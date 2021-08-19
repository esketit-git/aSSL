/* assl.h */

#ifndef BROWSER_H
#define BROWSER_H

#include <QtGui>
#include <QtWebKitWidgets>
#include <QBoxLayout>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(void) {
        content = new QWebView;

        layout = new QBoxLayout(QBoxLayout::TopToBottom);
        window = new QWidget;
        layout->setContentsMargins(0,0,0,0);

        content->setContextMenuPolicy(Qt::NoContextMenu); //diables context menu

        //content->setHtml(QString("<h1>Loading...</h1>"));

        layout->addWidget(content);
        window->setLayout(layout);
        setCentralWidget(window);

        QObject::connect(content, SIGNAL(loadFinished(bool)), this, SLOT(onLoadFinish(bool)));
        //QObject::connect(content, SIGNAL(loadProgress(int)), this, SLOT(onLoadProgress()));
    }

    void loadUrl(const QUrl url) {
       // content->load(QUrl::fromLocalFile&#40;"c://sample//index.html"&#41;&#41;;
        content->load(url);
        content->setFocus();
        content->show();
    }

protected slots:

    void onLoadFinish(bool ok) {
        setWindowTitle(QString("%1").arg(content->title()));

        if ( ! ok )
        {
          QString errorMsg( tr("<html><body>Error load %1.</body></html>").arg("https://container for assl middle ware.com/") );
          content->setHtml(errorMsg);
        }
    }

private:
    QWebView *content;
    QBoxLayout *layout;
    QWidget *window;
};

#endif // BROWSER_H
