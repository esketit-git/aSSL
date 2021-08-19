#include "assl.h"

int main(int argc, char** argv) {

    QApplication app(argc, argv);
    MainWindow window;
    window.showMaximized();

    window.loadUrl(QUrl("http://changethistoasslsiteformiddleware.com/"));
        window.setFocus();

//    window.showFullScreen();
//   window.setCursor(Qt::BlankCursor);

    return app.exec();
}
