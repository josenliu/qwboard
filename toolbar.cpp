#include "consdefine.h"
#include "toolbar.h"
#include "ui_toolbar.h"

ToolBar::ToolBar(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ToolBar)
{
    ui->setupUi(this);

    QRect rect = geometry();
    rect.setX(TOOL_BAR_STARTX);
    rect.setY(TOOL_BAR_STARTY);
    rect.setHeight(TOOL_BAR_HEIGHT);
    setGeometry(rect);

    m_operaCode = opCode::OP_CODE_SHAPE|drawMode::DRAW_CODE_LINE;

    connect(ui->shapeButton, SIGNAL(clicked()), this, SLOT(onShapeClicked()));
    connect(ui->pasteButton, SIGNAL(clicked()), this, SLOT(onPasteClicked()));
    connect(ui->copyButton, SIGNAL(clicked()), this, SLOT(onCopyClicked()));
    connect(ui->cutButton, SIGNAL(clicked()), this, SLOT(onCutClicked()));
    connect(ui->textButton, SIGNAL(clicked()), this, SLOT(onTextClicked()));
    connect(ui->tableButton, SIGNAL(clicked()), this, SLOT(onTableClicked()));
    connect(ui->selButton, SIGNAL(clicked()), this, SLOT(onSelectClicked()));

}

void ToolBar::resizeEvent(QResizeEvent *size)
{
    QRect rect = ui->titleText->geometry();
    double w = size->size().width() * TITLEBLOCK_WIDTH_COEF - BUTTONS_GAP - SPLITTER_WIDTH;
    if (w < TITLEBLOCK_LIMITED_WIDTH) w = TITLEBLOCK_LIMITED_WIDTH;
    rect.setWidth(int(w));
    rect.setHeight(PASTE_BUTTON_WIDTH);
    ui->titleText->setGeometry(rect);
    QFont tmpfnt = ui->titleText->font();
    tmpfnt.setPointSize(12 * int(w) / 100);
    ui->titleText->setFont(tmpfnt);

    ui->titleText->setAlignment(Qt::AlignCenter);

    int p = int(w) + BUTTONS_GAP;
    rect = ui->line1->geometry();
    rect.setX(p);
    rect.setSize(QSize(SPLITTER_WIDTH, BUTTON_COMMON_HEIGHT));
    ui->line1->setGeometry(rect);

    p += SPLITTER_WIDTH + BUTTONS_GAP;
    rect = ui->pasteButton->geometry();
    rect.setX(p);
    rect.setSize(QSize(PASTE_BUTTON_WIDTH, PASTE_BUTTON_HEIGHT));
    ui->pasteButton->setGeometry(rect);

    p += PASTE_BUTTON_WIDTH + BUTTONS_GAP;
    rect = ui->cutButton->geometry();
    rect.setX(p);
    rect.setSize(QSize(BUTTON_COMMON_WIDTH, BUTTON_COMMON_HEIGHT));
    ui->cutButton->setGeometry(rect);

    p += BUTTON_COMMON_WIDTH + BUTTONS_GAP;
    rect = ui->copyButton->geometry();
    rect.setX(p);
    rect.setSize(QSize(BUTTON_COMMON_WIDTH, BUTTON_COMMON_HEIGHT));
    ui->copyButton->setGeometry(rect);

    p += BUTTON_COMMON_WIDTH + BUTTONS_GAP;
    rect = ui->line2->geometry();
    rect.setX(p);
    rect.setSize(QSize(SPLITTER_WIDTH, BUTTON_COMMON_HEIGHT));
    ui->line2->setGeometry(rect);

    p += SPLITTER_WIDTH + BUTTONS_GAP;
    rect = ui->selButton->geometry();
    rect.setX(p);
    rect.setSize(QSize(BUTTON_COMMON_WIDTH, TEXT_BUTTON_HEIGHT));
    ui->selButton->setGeometry(rect);

    p += BUTTON_COMMON_WIDTH + BUTTONS_GAP;
    rect = ui->textButton->geometry();
    rect.setX(p);
    rect.setSize(QSize(TEXT_BUTTON_WIDTH, TEXT_BUTTON_HEIGHT));
    ui->textButton->setGeometry(rect);

    p += TEXT_BUTTON_WIDTH + BUTTONS_GAP;
    rect = ui->shapeButton->geometry();
    rect.setX(p);
    rect.setSize(QSize(BUTTON_COMMON_WIDTH, BUTTON_COMMON_HEIGHT));
    ui->shapeButton->setGeometry(rect);

    p += BUTTON_COMMON_WIDTH + BUTTONS_GAP;
    rect = ui->tableButton->geometry();
    rect.setX(p);
    rect.setSize(QSize(BUTTON_COMMON_WIDTH, BUTTON_COMMON_HEIGHT));
    ui->tableButton->setGeometry(rect);
}

void ToolBar::onSelectClicked()
{
    m_operaCode = opCode::OP_CODE_SELECT;
    emit selectModeChanged(m_operaCode);
}

void ToolBar::onShapeClicked()
{
    qint16 op = drawMode::DRAW_CODE_LINE;
    if ((m_operaCode&opCode::OP_CODE_MASK) == opCode::OP_CODE_SHAPE)
    {
        op = m_operaCode&0x00ff;
        op++;
        if (op == drawMode::DRAW_CODE_END) op = drawMode::DRAW_CODE_LINE;
    }

    m_operaCode = opCode::OP_CODE_SHAPE | op;
    emit shapeModeChanged(m_operaCode);
}

void ToolBar::onPasteClicked()
{
    m_operaCode = opCode::OP_CODE_PASTE;
    emit pasteModeChanged(m_operaCode);
}


void ToolBar::onCopyClicked()
{
    m_operaCode = opCode::OP_CODE_COPY;
    emit copyModeChanged(m_operaCode);
}

void ToolBar::onCutClicked()
{
    m_operaCode = opCode::OP_CODE_CUT;
    emit cutModeChanged(m_operaCode);
}

void ToolBar::onTextClicked()
{
    m_operaCode = opCode::OP_CODE_TEXT;
    emit textModeChanged(m_operaCode);
}

void ToolBar::onTableClicked()
{
    m_operaCode = opCode::OP_CODE_TABLE;
    emit tableModeChanged(m_operaCode);
}

ToolBar::~ToolBar()
{
    delete ui;
}
