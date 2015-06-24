#include "webviewwindow.h"

Webview::Webview() : QWebView()
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("About Qt");
}
