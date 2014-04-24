import QtQuick 2.0

Canvas {
    id: canvas
    width: 320
    height: 280
    antialiasing: true

    // need init
    property int topLeftRadius: 4
    property int topRightRadius: 4
    property int bottomLeftRadius: 4
    property int bottomRightRadius: 4

    property int lineWidth: 0
    property real alpha: 1.0
    property int shadowWidth: 0
    property real arrowPosition: 0.9
    property int arrowWidth: 11
    property int arrowHeight: 6

    property bool fill: true
    property color fillStyle: "#b4b4b4"

    property bool stroke: true
    property color strokeStyle: "white"
    // need init

    property int rectx: shadowWidth + lineWidth
    property int rectWidth: width - 2*rectx
    property int recty: shadowWidth + 2 * lineWidth
    property int rectHeight: height - rectx - recty

    onArrowPositionChanged: requestPaint();
    onFillChanged: requestPaint();
    onStrokeChanged: requestPaint();

    onPaint: {
        var ctx = getContext("2d");
        ctx.save();
        ctx.clearRect(0,0,canvas.width, canvas.height);
        ctx.strokeStyle = canvas.strokeStyle;
        ctx.lineWidth = canvas.lineWidth
        ctx.fillStyle = canvas.fillStyle
        ctx.globalAlpha = canvas.alpha
        ctx.beginPath();
        ctx.moveTo(rectx+topLeftRadius,recty);                 // top side

        // draw top right corner
        ctx.lineTo(rectx+rectWidth - topRightRadius,recty);
        ctx.arcTo(rectx+rectWidth, recty, rectx+rectWidth, recty+topRightRadius, topRightRadius);

        // draw bottom right corner
        ctx.lineTo(rectx+rectWidth,recty+rectHeight-bottomRightRadius);    // right side
        ctx.arcTo(rectx+rectWidth,recty+rectHeight,rectx+rectWidth-bottomRightRadius,recty+rectHeight,bottomRightRadius);

        // draw bottom left corner
        ctx.lineTo(rectx+bottomLeftRadius,recty+rectHeight);              // bottom side
        ctx.arcTo(rectx,recty+rectHeight,rectx,recty+rectHeight-bottomLeftRadius,bottomLeftRadius);
        ctx.lineTo(rectx,recty+topLeftRadius);                 // left side

        // draw top left corner
        ctx.arcTo(rectx,recty,rectx+topLeftRadius,recty,topLeftRadius);
        ctx.closePath();
        if (canvas.fill)
            ctx.fill();
        if (canvas.stroke)
            ctx.stroke();
        ctx.restore();
    }
}