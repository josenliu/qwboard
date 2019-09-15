#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QFrame>
#include <QResizeEvent>
#include <QDebug>

namespace Ui {
class ToolBar;
}

class ToolBar : public QFrame
{
    Q_OBJECT

public:
    explicit ToolBar(QWidget *parent = nullptr);
    ~ToolBar();

Q_SIGNALS:
    void selectModeChanged(qint16 mode);
    void shapeModeChanged(qint16 mode);
    void pasteModeChanged(qint16 mode);
    void cutModeChanged(qint16 mode);
    void copyModeChanged(qint16 mode);
    void textModeChanged(qint16 mode);
    void tableModeChanged(qint16 mode);

public Q_SLOTS:
    void onPasteClicked();
    void onCutClicked();
    void onCopyClicked();
    void onTextClicked();
    void onShapeClicked();
    void onTableClicked();
    void onSelectClicked();

protected:
    void resizeEvent(QResizeEvent *size);

private:
    Ui::ToolBar *ui;

    qint16 m_operaCode;

};

#endif // TOOLBAR_H
