/****************************************************************************
**
**  Copyright (C) 2011~2014 Deepin, Inc.
**                2011~2014 Kaisheng Ye
**
**  Author:     Kaisheng Ye <kaisheng.ye@gmail.com>
**  Maintainer: Kaisheng Ye <kaisheng.ye@gmail.com>
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

import QtQuick 2.1
import "calendar_core.js" as CalendarCore
import Deepin.Widgets 1.0

Column {
    id: calendarWidget
    width: 308
    height: childrenRect.height

    property string currentDateValue: CalendarCore.dateToString(globalDate)
    property string currentSelectedDateValue: currentDateValue

    property bool slideStop: true
    property bool isToday: currentDateValue == currentSelectedDateValue
    property var cur_calendar;
    property var pre_calendar;
    property var next_calendar;

    onCurrentSelectedDateValueChanged: {
        monthChange(currentSelectedDateValue)
    }

    function initTooltip(dateString){
//        var dateString = CalendarCore.dateToString(globalDate)
        if (dateString == "")
            return
        var dateValue = dateString.split("-")

        var year = dateValue[0]
        var month = dateValue[1]
        var date = dateValue[2]

        var lunarDayInfo = dbusLunarCalendar.GetLunarInfoBySolar(year,month,date)

        var tipStr = ""
        if(dsslocale.lang == "zh_CN"){
            if(lunarDayInfo[1]){
                var info = lunarDayInfo[0]
                tipStr = info[3] + info[4]
                if(info[8]){
                    tipStr += "\n" + info[8]
                }
                if(info[9]){
                    tipStr += "\n" + info[9]
                }
            }

        }

        tooltipLabel.text = tipStr.replace(/[\r\n]/g,"  ")
    }

    function monthChange(dateValue){
        var tmpYearMonth = CalendarCore.getYearMonth(dateValue)
        if(cur_calendar == undefined){
            return
        }
        if (CalendarCore.compareYearMonth(tmpYearMonth, cur_calendar.yearMonth) == 1 && slideStop){
            next_calendar = calendarSlideBox.createCanlendar(tmpYearMonth, "next")
            next_calendar.visible = true
            if (!toNextMonth.running && !toPreviousMonth.running){
                toNextMonth.restart()
            }
        }
        else if (CalendarCore.compareYearMonth(tmpYearMonth, cur_calendar.yearMonth) == -1 && slideStop){
            pre_calendar = calendarSlideBox.createCanlendar(tmpYearMonth, "previous")
            pre_calendar.visible = true
            if (!toNextMonth.running && !toPreviousMonth.running){
                toPreviousMonth.restart()
            }
        }
    }

    ParallelAnimation {
        id: toNextMonth
        onStarted: {
            slideStop = false
        }
        PropertyAnimation {
            target: cur_calendar
            properties: "x"
            to: calendarSlideBox.x - calendarSlideBox.width
            easing.type: Easing.InOutQuad
            duration: 300
        }
        PropertyAnimation {
            target: next_calendar
            properties: "x"
            to: calendarSlideBox.x
            easing.type: Easing.InOutQuad
            duration: 300
        }
        onStopped: {
            cur_calendar.destroy()
            cur_calendar = next_calendar
            slideStop = true
        }
    }

    ParallelAnimation {
        id: toPreviousMonth
        onStarted: {
            slideStop = false
        }
        PropertyAnimation {
            target: pre_calendar
            properties: "x"
            to: calendarSlideBox.x
            easing.type: Easing.InOutQuad
            duration: 300
        }
        PropertyAnimation {
            target: cur_calendar
            properties: "x"
            to: calendarSlideBox.x + calendarSlideBox.width
            easing.type: Easing.InOutQuad
            duration: 300
        }
        onStopped: {
            cur_calendar.destroy()
            cur_calendar = pre_calendar
            slideStop = true
        }
    }

    DBaseLine {
        id: dateBoxAdjustment
        height: 38
        color: "#1a1b1b"

        leftLoader.sourceComponent: YearMonthAdjustor {
            id:yearMonthAdjustor
            canAdjustMonth: slideStop
            height: dateBoxAdjustment.height
            dateValue: calendarWidget.currentSelectedDateValue
            onMonthChanged:calendarWidget.currentSelectedDateValue = newDateString
        }

        rightLoader.sourceComponent: DTextAction {
            anchors.verticalCenter: parent.verticalCenter
            text: dsTr("Today")
            visible: opacity != 0
            opacity: isToday ? 0 : 1
            onClicked: {
                calendarWidget.initTooltip(CalendarCore.dateToString(globalDate))
                if(CalendarCore.compareYearMonth(currentDateValue, calendarWidget.currentSelectedDateValue) == 0){
                    calendarWidget.currentSelectedDateValue = currentDateValue
                }
                else{
                    calendarWidget.currentSelectedDateValue = currentDateValue
                }
            }
        }

    }

    Rectangle {
        id: tooltipRec
        height: tooltipLabel.visible ? 25 : 0
        enabled: tooltipLabel.visible
        width: parent.width

        property string dateText:""

        color: "#1a1b1b"

        DLabel {
            id:tooltipLabel
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 15
            font.pixelSize: 11
            verticalAlignment: Text.AlignVCenter
            height: parent.height
            visible: text != ""
        }
    }

    Rectangle {
        id: calendarSlideBox
        width: parent.width
        height: cur_calendar.height
        property var component: Qt.createComponent("CalendarComponent.qml")

        function initCalendar(){
            var yearMonth = CalendarCore.getYearMonth(currentSelectedDateValue)
            cur_calendar = createCanlendar(yearMonth, '');

            pre_calendar = cur_calendar
            next_calendar = cur_calendar
        }

        Component.onCompleted: {
            initCalendar()
            calendarWidget.currentSelectedDateValue = CalendarCore.dateToString(globalDate)
            initTooltip(CalendarCore.dateToString(globalDate))
        }

        function createCanlendar(yearMonth, position){
            var calendar = calendarSlideBox.component.createObject(calendarSlideBox, {
                "yearMonth": yearMonth
            })

            if (position == 'previous'){
                calendar.x = calendarSlideBox.x - calendarSlideBox.width;
                calendar.visible = false
            }
            else if (position == 'next') {
                calendar.x = calendarSlideBox.x + calendarSlideBox.width;
                calendar.visible = false
            }
            else {
                calendar.x = calendarSlideBox.x
            }
            return calendar
        }

    }

    DSeparatorHorizontal {}
}