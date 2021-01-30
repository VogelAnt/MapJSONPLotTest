import QtQuick 2.14
import QtQuick.Window 2.14
import QtLocation 5.14
import QtPositioning 5.14
import QtQuick.Controls 2.12

Item{
    id: customMap
    visible: true
    width: 640
    height: 480
    property int markerCount: 0
    property int currentIndex: -1
    property bool singleScenario: false
    property bool drawScenario: false
    property string brd_clr: "#f5f5f5"
    Connections{
        target: markerModel
            onComboBoxSelectionChanged:{
                polygonmodel.clear()
//                polygon.path.clear()
                console.log("RECEIVED CHANGE SIGNAL FROM C++ IN QML")
                markerCount = markerModel.resetMarkerCount()
            }
    }

    ListModel{
        id: polygonmodel
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: Plugin {
            name: "osm"
        }

        gesture.enabled: currentIndex == -1
        center: QtPositioning.coordinate(59.91, 10.75) // Oslo
        zoomLevel: 14
        MapItemView{
            z: polygon.z + 1
            model: polygonmodel
            delegate: MapQuickItem{
                anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height)
                coordinate: QtPositioning.coordinate(model.coords.latitude, model.coords.longitude)
                sourceItem: Image {
                    width: 50
                    height: 50
                    source: "qrc:/../../Downloads/map+marker+icon-1320166582858325800_64.png"
                    MouseArea{
                        anchors.fill: parent
                        acceptedButtons: Qt.LeftButton
                        propagateComposedEvents: true
                        onPressed: {
                            currentIndex = index
                            mouse.accepted = false
                            console.log("Latitiude: " + model.coords.latitude)
                            console.log("Longitude: " + model.coords.longitude)
                        }
                    }
                }
            }
        }

        MapPolygon{
            id: polygon
            opacity: 0.6
            border.color: "transparent"
            border.width: 5
        }

        MouseArea{
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onDoubleClicked: {
                var point = Qt.point(mouse.x, mouse.y)
                var coord = map.toCoordinate(point);
                if (mouse.button == Qt.LeftButton){
                    if(markerModel.getSingleScenarioStatus()){
                        console.log("IN SINGLE SCENARIO SELECTED")
                        if(markerModel.getMarkerCount() < 1){
                            addMarker(coord)
                            markerModel.increaseMarkerCount()
                            markerModel.addMarker(coord)
                            changeBorderColor()
                            console.log("Added marker at "+coord)
                        }
                    }
                    else if(markerModel.getDrawScenarioStatus()){
                        // TODO: change marker color to
                        addMarker(coord)
                        changeBorderColor()
                        markerModel.increaseMarkerCount()
                        markerModel.addMarker(coord)
                        console.log("Added marker at "+coord)
                    }
                    else{
                        addMarker(coord)
                        changeBorderColor()
                        markerModel.increaseMarkerCount()
                        markerModel.addMarker(coord)
                        console.log("Added marker at "+coord)
                    }
                }
            }

            onClicked:
                if(mouse.button == Qt.RightButton){
                    if(markerCount >= 0){
                        var point = Qt.point(mouse.x, mouse.y)
                        var coord = map.toCoordinate(point);
                        polygonmodel.remove(0, markerCount)
                        markerCount = markerCount -1
                    }
                }

            onPositionChanged: {
                if (currentIndex != -1){
                    console.log("NOW IN POSITION CHANGED")
                    var point = Qt.point(mouse.x, mouse.y)
                    var coord = map.toCoordinate(point);
                    if(coord.isValid)
                        moveMarker(currentIndex, coord)
                        console.log(markerCount)
                        markerModel.changeMarkerPosition(markerCount, coord)
                }
            }

            onReleased: {
                if (mouse.button == Qt.LeftButton && currentIndex != -1){
                    console.log("NOW IN RELEASED MOUSE")
                    var point = Qt.point(mouse.x, mouse.y)
                    var coord = map.toCoordinate(point);
                    if(coord.isValid)
                        moveMarker(currentIndex, coord)
                        markerModel.changeMarkerPosition(markerCount, coord)

                    currentIndex = -1;
                }
            }
        }
    }

    function moveMarker(index, coordinate){
        console.log("MOVING MARKER")
        polygonmodel.set(index, {"coords": coordinate})
        // This part adapts the polygon path when the marker has been moved
        var path = polygon.path;
        path[index] = coordinate
        polygon.path = path
//        polygon.removeCoordinate(polygon.path)
    }

    function clearPath(){

    }

    function removeMarker(){
        polygon.removeCoordinate()
    }

    function addMarker(coordinate){
        polygonmodel.append({"coords": coordinate})
        polygon.addCoordinate(coordinate)
        console.log(markerCount)
        markerCount = markerCount+1
    }

    function changeBorderColor(){
        if(markerModel.getDrawScenarioStatus()){
            console.log("SETTING COLOR TO YELLOW")
            polygon.border.color = "yellow"
        }
        else{
            polygon.border.color = "transparent"
            console.log("SETTING COLOR TO TRANSPARENT")
        }
    }
}
