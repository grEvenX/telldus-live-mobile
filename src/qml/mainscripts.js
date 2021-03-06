var FAVORITE = 1;
var DEVICE = 2;
var SENSOR = 3;
var SETTING = 4;
var FULL_FAVORITE_LAYOUT = 5;
var FULL_DEVICE = 6;
var FULL_SENSOR = 7;
var SCHEDULER = 8;
var FULL_SETTING = 9;

var METHOD_TURNON = 1;
var METHOD_TURNOFF = 2;
var METHOD_BELL = 4;
var METHOD_DIM = 16;

var DEVICETYPE = 0;
var GROUPTYPE = 1;

function getFriendlyText(mode){
	if(mode == FAVORITE){
		return "\u2605 Favorites";
	}
	else if(mode == DEVICE){
		return "\u2615 Devices";
	}
	else if(mode == SENSOR){
		return "\u2614 Sensors";
	}
	else if(mode == SETTING){
		return "\u2692 Settings";
	}
	else if(mode == FULL_FAVORITE_LAYOUT){
		return "\u2328";  //TODO icons instead
	}
	else if(mode == FULL_DEVICE){
		return "\u2615";  //TODO icons instead
	}
	else if(mode == FULL_SENSOR){
		return "\u2614";  //TODO icons instead
	}
	else if(mode == SCHEDULER){
		return "\u1F552";  //TODO icons instead
	}
	else if(mode == FULL_SETTING){
		return "\u2692";  //TODO icons instead
	}
}

function getIconSource(mode){
	if(mode == FULL_FAVORITE_LAYOUT){
		//TODO
	}
	return ''
}

function methodContains(methods, method){
	//TODO constants...
	var methodid = 0
	if(method == "on"){
		methodid = 1;
	}
	else if(method == "off"){
		methodid = 2;
	}
	else if(method == "bell"){
		methodid = 4;
	}
	else if(method == "dim"){
		methodid = 16;
	}
	//pad specific:
	else if(method == "toggle"){
		return methods & 1 && methods & 2; //on AND off
	}
	else if(method == "slider"){
		methodid = 16; //same as dim
	}

	//TODO stop, up, down (, execute)

	return (methods & methodid);
}

var DEFAULTBUTTONHEIGHT = 40 * SCALEFACTOR;
var DEVICEROWHEIGHT = 50 * SCALEFACTOR;
var HEADERHEIGHT = 20 * SCALEFACTOR;
var INFOBUBBLEHEIGHT = 200 * SCALEFACTOR;
var INFOBUBBLEWIDTH = 200 * SCALEFACTOR;
var LISTWIDTH = 300 * SCALEFACTOR;
var MAINHEADERHEIGHT = 20 * SCALEFACTOR;
var MARGIN_TEXT = 10 * SCALEFACTOR;
var MENUOPTIONHEIGHT = 30 * SCALEFACTOR;
var SLIDERHEIGHT = 30 * SCALEFACTOR;
var SLIDERWIDTH = 20 * SCALEFACTOR;
var SUBHEADERHEIGHT = 20 * SCALEFACTOR;
var TOOLBARHEIGHT = 50 * SCALEFACTOR;
var TOOLBARWIDTH = 100 * SCALEFACTOR; //TODO this should be dependent on the widest button text... Possible?
var VISUALDEVICEHEIGHT = 20 * SCALEFACTOR;
var VISUALDEVICEWIDTH = 20 * SCALEFACTOR;
var VISUALSENSORWIDTH = 80 * SCALEFACTOR;
