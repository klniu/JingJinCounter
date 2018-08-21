import QtQuick 2.11
import QtQuick.Controls 1.4
import QtQuick.Window 2.0

ApplicationWindow {
	id: root
	visible: true
    property int counterValue: 0
    width: getReactWidth(counterValue)
	height: 40
	x: Screen.width - width
	y: Screen.height - height
	flags: Qt.Tool | Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint
	color: "transparent"

	function read(fname) {
		var req = new XMLHttpRequest()
		req.open("GET", "file://" + fname, false)
		req.send()
		return req.responseText
	}

    function getReactWidth(v) {
        var width = 12 * counterValue.toString().length + 20
        return width > 50 ? width:50
    }

    Shortcut {
        sequence: "F22"
        onActivated: counterValue++
    }

    Rectangle {
        radius: 10
        color: "green"
        width: getReactWidth(counterValue)
        height: parent.height
        Text {
            font.pixelSize: 20
            font.letterSpacing: 1.2
            anchors.centerIn: parent
            color: "white"
            font.bold: true
            text: counterValue
        }
    }

	MouseArea {
		anchors.fill: parent
		property int mx: 0
		property int my: 0
		onPressed: {
			mx = mouseX
			my = mouseY
		}
		onPositionChanged: {
			root.x += mouseX - mx
			root.y += mouseY - my
		}
	}
}
