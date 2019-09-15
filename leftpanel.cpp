#include "consdefine.h"
#include "leftpanel.h"
#include "ui_leftpanel.h"

LeftPanel::LeftPanel(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::LeftPanel)
{
    ui->setupUi(this);

    QRect rect = geometry();
    rect.setX(LEFT_PANEL_STARTX);
    rect.setY(LEFT_PANEL_STARTY);
    rect.setWidth(LEFT_PANEL_WIDTH);
    setGeometry(rect);

    connect(ui->expButton, SIGNAL(pressed()), this, SLOT(onExpButtonPressed()));
    connect(ui->optButton, SIGNAL(pressed()), this, SLOT(onOptButtonPressed()));
}

void LeftPanel::resizeEvent(QResizeEvent *size)
{
    QRect rect = ui->shareButton->geometry();
    int nxp = PANEL_BUTTON_STARTY + PANEL_BUTTON_COMMON_WIDTH + PANEL_BUTTON_COMMON_GAP;

    rect.setY(size->size().height() - nxp);
    rect.setSize(QSize(PANEL_BUTTON_COMMON_WIDTH, PANEL_BUTTON_COMMON_HEIGHT));
    ui->shareButton->setGeometry(rect);

    nxp += PANEL_BUTTON_COMMON_GAP + PANEL_BUTTON_COMMON_WIDTH;
    rect.setY(size->size().height() - nxp);
    rect.setSize(QSize(PANEL_BUTTON_COMMON_WIDTH, PANEL_BUTTON_COMMON_HEIGHT));
    ui->optButton->setGeometry(rect);

    nxp += PANEL_BUTTON_COMMON_GAP + PANEL_BUTTON_COMMON_WIDTH;
    rect.setY(size->size().height() - nxp);
    rect.setSize(QSize(PANEL_BUTTON_COMMON_WIDTH, PANEL_BUTTON_COMMON_HEIGHT));
    ui->settingsButton->setGeometry(rect);

    nxp += PANEL_BUTTON_COMMON_GAP + PANEL_BUTTON_COMMON_WIDTH;
    rect.setY(size->size().height() - nxp);
    rect.setSize(QSize(PANEL_BUTTON_COMMON_WIDTH, PANEL_BUTTON_COMMON_HEIGHT));
    ui->userButton->setGeometry(rect);
}

void LeftPanel::onExpButtonPressed()
{
    emit expButtonPressed();
}

void LeftPanel::onOptButtonPressed()
{
    emit optButtonPressed();
}

LeftPanel::~LeftPanel()
{
    delete ui;
}
