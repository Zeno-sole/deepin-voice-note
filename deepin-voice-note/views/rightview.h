#ifndef RIGHTVIEW_H
#define RIGHTVIEW_H

#include <QVBoxLayout>

#include <DWidget>
#include <DDialog>

DWIDGET_USE_NAMESPACE
struct VNoteItem;
struct VNoteBlock;
struct VNVoiceBlock;

class VoiceNoteItem;

class RightView : public DWidget
{
    Q_OBJECT
public:
    explicit RightView(QWidget *parent = nullptr);
    void initData(VNoteItem *data);
    DWidget *insertVoiceItem(const QString &voicePath, qint64 voiceSize);
    DWidget *insertTextEdit(VNoteBlock* data, bool focus = false);
    void  setEnablePlayBtn(bool enable);
    void  delWidget(DWidget *widget);
    void  updateData();
    VoiceNoteItem *getVoiceItem(VNoteBlock* data);
    VoiceNoteItem *getMenuVoiceItem();
signals:
    void sigVoicePlay(VNVoiceBlock *voiceData);
    void sigVoicePause(VNVoiceBlock *voiceData);
    void contentChanged();
public slots:
    void onTextEditFocusIn();
    void onTextEditFocusOut();
    void onTextEditDelEmpty();
    void onTextEditTextChange();
    void onVoicePlay(VoiceNoteItem *item);
    void onVoicePause(VoiceNoteItem *item);
    void onVoiceMenuShow();
protected:
    void leaveEvent(QEvent *event) override;
    void saveNote();
    void adjustVerticalScrollBar(QWidget *widget, int defaultHeight);
private:
    void initUi();
    void initMenu();
    bool        checkFileExist(const QString & file);
    VoiceNoteItem *m_menuVoice {nullptr};
    VNoteItem   *m_noteItemData {nullptr};
    DWidget     *m_curItemWidget{nullptr};
    DWidget     *m_viewportWidget {nullptr};
    DWidget     *m_placeholderWidget {nullptr};
    QVBoxLayout *m_viewportLayout {nullptr};
    QScrollArea *m_viewportScrollArea {nullptr};
    //Voice control context menu
    DMenu       *m_voiceContextMenu {nullptr};
    DDialog     *m_fileHasDelDialog {nullptr};
    bool         m_fIsNoteModified {false};
};

#endif // RIGHTVIEW_H
