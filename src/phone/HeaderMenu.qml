import QtQuick 1.0

Item {
	id: headerMenu
	property alias items: children.children
	property alias activeItem: children.activeItem
	height: 57*SCALEFACTOR
	anchors.top: header.bottom
	anchors.left: parent.left
	anchors.right: parent.right
	Image {
		height: 67
		width: parent.width/SCALEFACTOR
		anchors.top: parent.top
		source: "headerMenuBg.png"
		fillMode: Image.TileHorizontally
		scale: SCALEFACTOR
		transformOrigin: Item.TopLeft
	}
	Row {
		id: children
		property variant activeItem
		anchors.fill: parent
	}
}
