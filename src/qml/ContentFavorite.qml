import Qt 4.7

Content{
	id: contentFavorite

	ListView {
		id: favoritelist
		anchors.horizontalCenter: parent.horizontalCenter
		height: parent.height
		width: parent.width

		model: favoriteModel

		delegate: DeviceElement {
			hideFavoriteToggle: true
		}
	}
}