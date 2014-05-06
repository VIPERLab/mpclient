import QtQuick 2.0

Rectangle {
	property variant model;
	height: 100

	Component {
		id: channelDelegate
		StationView {
			width : 120
		}
	}

	StyledText  {
		id: lastStationsText
		text: 'ПОСЛЕДНИЕ'
		color: '#ff7e43'
		font.pixelSize: 13
	}
	
	ListView {
		id: channelsList
		
		anchors {
			fill: parent
			topMargin: 30
		}
		
		interactive: false
		delegate: channelDelegate
		model: parent.model
		height: 75
	}
}
