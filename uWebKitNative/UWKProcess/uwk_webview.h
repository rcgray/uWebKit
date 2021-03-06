
/******************************************
  * uWebKit 
  * (c) 2014 THUNDERBEAST GAMES, LLC
  * website: http://www.uwebkit.com email: sales@uwebkit.com
  * Usage of this source code requires a uWebKit Source License
  * Please see UWEBKIT_SOURCE_LICENSE.txt in the root folder 
  * for details
*******************************************/

#pragma once

#include <QtWebKitWidgets>
#include <QGraphicsView>
#include <QGraphicsWebView>

#include "UWKCommon/uwk_message.h"

// IMPORTANT: Usage of this source code requires a uWebKit Source License
// please see the UWEBKIT_SOURCE_LICENSE.txt in the root folder
#define GITHUB_BUILD

namespace UWK
{

class GpuSurface;
class WebPage;

class WebView : public QGraphicsWebView
{
    Q_OBJECT

    enum MouseButtons
    {
        ButtonLeft = 0,
        ButtonRight = 1,
        ButtonMiddle = 2,
        Max = 3
    };

    bool buttonState_[3];


    uint32_t id_;
    int maxWidth_;
    int maxHeight_;

    int currentWidth_;
    int currentHeight_;

    // format being Format_ARGB32_Premultiplied is extremely important to avoid
    // a painter transform when rendering web page
    // this is the resolution of the gpu texture
    QImage gpuImage_;

    // the page image which is rendered at currentWidth_ and currentHeight_
    QImage pageImage_;

    QSize frameContentsSize_;
    WebPage* page_;
    QGraphicsView* graphicsView_;
    QGraphicsScene* scene_;

    bool rendering_;
    GpuSurface* gpuSurface_;

    bool cursorDraw_;
    QDateTime cursorBlinkTime_;

    // as we're using offscreen rendering store vibility here
    // as well
    bool visible_;

    int progress_;

    int timerId_;

    QBuffer cachedIcon_;

    void checkIcon();

    void adjustSize(int width, int height);

    void registerIMEHandler();
    void setIME(const QString& ime);

#ifdef GITHUB_BUILD

    QStaticText githubText_;

#endif

private slots:
        void handleSslErrors(QNetworkReply* reply, const QList<QSslError> &errors);

public slots:

    void loadFinished(bool ok);
    void urlChanged(const QUrl& url);
    void titleChanged(const QString& title);
    void loadStarted();
    void setProgress( int progress);
    void javaScriptWindowObjectCleared();

    void handleFocusIn(QVariant type, QVariant var, QVariant left, QVariant top, QVariant width, QVariant height);
    void handleFocusOut(QVariant var);

protected:

    void timerEvent(QTimerEvent *event);

public:

    void ProcessUWKMessage(const UWKMessage& msg);
    uint32_t GetGPUSurfaceID();

    uint32_t GetID() { return id_; }


    WebView(uint32_t id, int maxWidth, int maxHeight);
    ~WebView();


};

}
