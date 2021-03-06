#include "devicemodel.h"
#include "device.h"
#include "tellduslive.h"

class DeviceModel::PrivateData {
public:
	static DeviceModel *instance;
};
DeviceModel *DeviceModel::PrivateData::instance = 0;

DeviceModel::DeviceModel(QObject *parent) :
	TListModel("device", parent)
{
	connect(TelldusLive::instance(), SIGNAL(authorizedChanged()), this, SLOT(authorizationChanged()));
	this->authorizationChanged();
}

void DeviceModel::addDevices(const QVariantList &deviceList) {
	QList<QObject *> list;
	foreach(QVariant v, deviceList) {
		QVariantMap dev = v.toMap();

		Device *device = this->findDevice(dev["id"].toInt());
		if (!device) {
			device = new Device(this);
			device->setId(dev["id"].toInt());
			list << device;
		}
		if (dev.contains("isfavorite")) {
			device->setIsFavorite(dev["isfavorite"].toBool());
		}
		device->setMethods(dev["methods"].toInt());
		device->setName(dev["name"].toString());
		device->setClientName(dev["clientName"].toString());
		device->setOnline(dev["online"].toBool());
		device->setState(dev["state"].toInt());
		device->setStateValue(dev["statevalue"].toString());
		if (dev["type"].type() == QVariant::String) {
			device->setType(dev["type"].toString());
		} else {
			device->setType(Device::Type(dev["type"].toInt()));
		}
		if (dev.contains("devices")) {
			device->addDevices(dev["devices"].toString(), false);
		}
	}
	if (list.size()) {
		//Appends all in one go
		this->append(list);
	}
}

void DeviceModel::authorizationChanged() {
	TelldusLive *telldusLive = TelldusLive::instance();
	if (telldusLive->isAuthorized()) {
		TelldusLiveParams params;
		params["supportedMethods"] = Device::TURNON | Device::TURNOFF | Device::BELL | Device::DIM | Device::LEARN | Device::UP | Device::DOWN | Device::STOP;
		telldusLive->call("devices/list", params, this, SLOT(onDevicesList(QVariantMap)));
	} else {
		this->clear();
	}
}

void DeviceModel::createGroup(int clientId, const QString &name, Device *dev) {
	TelldusLive *telldusLive = TelldusLive::instance();
	if (!telldusLive->isAuthorized()) {
		return;
	}
	TelldusLiveParams params;
	params["clientId"] = clientId;
	params["name"] = name;
	params["devices"] = dev->deviceId();
	telldusLive->call("group/add", params, this, SLOT(onGroupAdd(QVariantMap)));
}

Device *DeviceModel::findDevice(int id) const {
	for(int i = 0; i < this->rowCount(); ++i) {
		Device *device = qobject_cast<Device *>(this->get(i).value<QObject *>());
		if (!device) {
			continue;
		}
		if (device->deviceId() == id) {
			return device;
		}
	}
	return 0;
}

DeviceModel * DeviceModel::instance() {
	if (PrivateData::instance == 0) {
		PrivateData::instance = new DeviceModel;
	}
	return PrivateData::instance;
}

void DeviceModel::onDeviceInfo(const QVariantMap &result) {
	QVariantList list;
	list << result;
	this->addDevices(list);
}

void DeviceModel::onDeviceRemove(const QVariantMap &result, const QVariantMap &params) {
	if (result["status"] != "success") {
		return;
	}
	for(int i = 0; i < this->rowCount(); ++i) {
		Device *device = qobject_cast<Device *>(this->get(i).value<QObject *>());
		if (!device) {
			continue;
		}
		if (device->deviceId() == params["id"].toInt()) {
			this->splice(i,1);
			return;
		}
	}
}

void DeviceModel::onDevicesList(const QVariantMap &result) {
	this->addDevices(result["device"].toList());
	emit devicesLoaded(result["device"].toList());
}

void DeviceModel::onGroupAdd(const QVariantMap &result) {
	if (result["status"].toString() != "success") {
		return;
	}

	TelldusLive *telldusLive = TelldusLive::instance();
	TelldusLiveParams params;
	params["id"] = result["id"];
	params["supportedMethods"] = 23; //TODO: Use constants
	telldusLive->call("device/info", params, this, SLOT(onDeviceInfo(QVariantMap)));
}

void DeviceModel::removeDevice(int id) {
	TelldusLive *telldusLive = TelldusLive::instance();
	TelldusLiveParams params;
	params["id"] = id;
	telldusLive->call("device/remove", params, this, SLOT(onDeviceRemove(QVariantMap,QVariantMap)), params);
}

