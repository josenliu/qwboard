#include "statusbar.h"
#include "ui_statusbar.h"

const QStringList operaCodeName = {
    QString("Paste"),
    QString("Copy"),
    QString("Cut"),
    QString("Select"),
    QString("Text"),
    QString("Shape"),
    QString("Table")
};

const QStringList drawModeName = {
    QString("Line"),
    QString("Rectangle"),
    QString("Circle"),
    QString("Ellipse"),
    QString("Text"),
    QString("Path")
};

StatusBar::StatusBar(QWidget *parent) :
    QStatusBar(parent),
    ui(new Ui::StatusBar)
{
    ui->setupUi(this);

    QRect rect = geometry();
    rect.setX(0);
    rect.setY(parent->geometry().height() - STATUS_BAR_HEIGHT);
    rect.setWidth(parent->geometry().width());
    setGeometry(rect);

    connect(ui->ZoomSlider, SIGNAL(valueChanged(int)), this, SLOT(zoomValueChanged(int)));
    connect(ui->ZoomPlus, SIGNAL(clicked()), this, SLOT(zoomPlusPressed()));
    connect(ui->ZoomMinus, SIGNAL(clicked()), this, SLOT(zoomMinusPressed()));
}

void StatusBar::resizeEvent(QResizeEvent *size)
{
    qDebug() << "status bar size: " << size->size();

    QRect rect = ui->drawName->geometry();
    int width = STATUS_BAR_DRAWNAME_WIDTH + STATUS_BAR_INTER_GAP +
            STATUS_BAR_MINUS_WIDTH + STATUS_BAR_SLIDER_WIDTH +
            STATUS_BAR_PLUS_WIDTH + STATUS_BAR_ZOOMNUM_WIDTH + STATUS_BAR_RIGHT_MARGIN;
    rect.setX(size->size().width() - width);
    rect.setWidth(STATUS_BAR_DRAWNAME_WIDTH);
    ui->drawName->setGeometry(rect);

    rect = ui->ZoomMinus->geometry();
    width = STATUS_BAR_MINUS_WIDTH + STATUS_BAR_SLIDER_WIDTH +
            STATUS_BAR_PLUS_WIDTH + STATUS_BAR_ZOOMNUM_WIDTH + STATUS_BAR_RIGHT_MARGIN;
    rect.setX(size->size().width() - width);
    rect.setWidth(STATUS_BAR_MINUS_WIDTH);
    ui->ZoomMinus->setGeometry(rect);
    qDebug() << "zoom minus: " << rect;

    rect = ui->ZoomSlider->geometry();
    width = STATUS_BAR_SLIDER_WIDTH + STATUS_BAR_PLUS_WIDTH +
            STATUS_BAR_ZOOMNUM_WIDTH + STATUS_BAR_RIGHT_MARGIN;
    rect.setX(size->size().width() - width);
    rect.setWidth(STATUS_BAR_SLIDER_WIDTH);
    ui->ZoomSlider->setGeometry(rect);
    qDebug() << "zoom slider: " << rect;

    rect = ui->ZoomPlus->geometry();
    width = STATUS_BAR_PLUS_WIDTH + STATUS_BAR_ZOOMNUM_WIDTH + STATUS_BAR_RIGHT_MARGIN;
    rect.setX(size->size().width() - width);
    rect.setWidth(STATUS_BAR_PLUS_WIDTH);
    ui->ZoomPlus->setGeometry(rect);
    qDebug() << "zoom plus: " << rect;

    rect = ui->ZoomNumber->geometry();
    width = STATUS_BAR_ZOOMNUM_WIDTH + STATUS_BAR_RIGHT_MARGIN;
    rect.setX(size->size().width() - width);
    rect.setWidth(STATUS_BAR_ZOOMNUM_WIDTH);
    ui->ZoomNumber->setGeometry(rect);
    qDebug() << "zoom number: " << rect;
}

void StatusBar::zoomValueChanged(int value)
{
    QString str = QString().setNum(value) + "%";

    ui->ZoomNumber->setText(str);

    emit zoomChanged(value);
}

void StatusBar::zoomPlusPressed()
{
    int value = ui->ZoomSlider->value();

    value++;
    if (value >= 200) value = 200;

    ui->ZoomSlider->setValue(value);
}

void StatusBar::zoomMinusPressed()
{
    int value = ui->ZoomSlider->value();

    if (value > 1) value--;

    ui->ZoomSlider->setValue(value);
}

void StatusBar::onOperaCodeChanged(qint16 code)
{
    qint16 opcode = code&qint16(opCode::OP_CODE_MASK);
    QString drawName = operaCodeName[opcode>>8];

    qint16 drawMode = code&0x00ff;

    if (opcode == opCode::OP_CODE_SHAPE) drawName += ": " + drawModeName[drawMode];

    ui->drawName->setText(drawName);

    qDebug() << "operation Code: " << drawName;
}

void StatusBar::onPositionChanged(QPoint pos)
{
    QString posText = "X: " + QString().setNum(pos.x()) + "  Y: " + QString().setNum(pos.y());
    ui->pos->setText(posText);
}

StatusBar::~StatusBar()
{
    delete ui;
}
