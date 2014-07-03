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

namespace UWK
{

class WebView;

class WebPage : public QWebPage
{
    Q_OBJECT

protected:

    WebView* view_;
    void javaScriptConsoleMessage ( const QString& message, int lineNumber, const QString& sourceID );

public:

    bool acceptNavigationRequest(QWebFrame *frame, const QNetworkRequest &request, NavigationType type);

    explicit WebPage(WebView* view);

public slots:

    void repaintRequested(const QRect & dirtyRect);

};

}
