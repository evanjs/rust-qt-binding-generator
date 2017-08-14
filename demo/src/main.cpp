#include "Tree.h"
#include "Bindings.h"
#include <cstdlib>

#include <KAboutData>
#include <KLocalizedString>
#include <KMessageBox>
#include <QApplication>
#include <QCommandLineParser>
#include <QTreeView>
#include <QQmlApplicationEngine>
#include <QtQml/qqml.h>
#include <QQmlContext>
#include <QDebug>
#include <QFileSystemModel>
#include <QStandardItemModel>
//#include "modeltest.h"

int main (int argc, char *argv[])
{
    QApplication app(argc, argv);
    KLocalizedString::setApplicationDomain("Demo");
    
    KAboutData aboutData(
                         // The program name used internally. (componentName)
                         QStringLiteral("Demo"),
                         // A displayable program name string. (displayName)
                         i18n("Demo"),
                         // The program version string. (version)
                         QStringLiteral("0.1"),
                         // Short description of what the app does. (shortDescription)
                         i18n("Demo application for Rust bindings"),
                         // The license this code is released under
                         KAboutLicense::GPL,
                         // Copyright Statement (copyrightStatement = QString())
                         i18n("(c) 2017"),
                         // Optional text shown in the About box.
                         // Can contain any information desired. (otherText)
                         i18n("Some text..."),
                         // The program homepage string. (homePageAddress = QString())
                         QStringLiteral("http://kde.org/"),
                         // The bug report email address
                         // (bugsEmailAddress = QLatin1String("submit@bugs.kde.org")
                         QStringLiteral("submit@bugs.kde.org"));
    aboutData.addAuthor(i18n("Jos van den Oever"), i18n("Task"), QStringLiteral("your@email.com"),
                         QStringLiteral("http://vandenoever.info"), QStringLiteral("OSC Username"));
    KAboutData::setApplicationData(aboutData);

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    aboutData.setupCommandLine(&parser);
    parser.process(app);
    aboutData.processCommandLine(&parser);

    qmlRegisterType<Directory>("rust", 1, 0, "Directory");
    qmlRegisterType<Person>("rust", 1, 0, "Person");

    QFileSystemModel m;
    m.setRootPath("/");
    qDebug() << m.rowCount();
    QModelIndex i = m.index(0,0);
    qDebug() << i;
    qDebug() << m.parent(i);
    qDebug() << m.data(i);
    qDebug() << m.rowCount(i) << m.canFetchMore(i);
    qDebug() << "---";
/*
    QStandardItemModel sm;
    sm.appendRow(new QStandardItem());
*/

    Tree model;
    //ModelTest test(&model);
    model.setPath("/");
    qDebug() << "rowCount()" << model.rowCount();
    i = model.index(0,0);
    qDebug() << i;
    qDebug() << model.parent(i);
    qDebug() << model.data(i);
    qDebug() << "rowCount(i)" << model.rowCount(i) << model.canFetchMore(i);
    model.fetchMore(i);
    model.fetchMore(model.index(1,0,i));
    model.fetchMore(model.index(2,0,i));
    model.fetchMore(model.index(3,0,i));
    model.fetchMore(model.index(4,0,i));
    model.fetchMore(model.index(5,0,i));
    qDebug() << "rowCount(i)" << model.rowCount(i) << model.canFetchMore(i);
    i = model.index(0, 0, i);
    model.fetchMore(model.index(1,0,i));
    model.fetchMore(model.index(2,0,i));
    model.fetchMore(model.index(3,0,i));
    model.fetchMore(model.index(4,0,i));
    model.fetchMore(model.index(5,0,i));
    qDebug() << "rowCount(i)" << model.data(i) << model.rowCount(i) << model.canFetchMore(i);
    model.fetchMore(i);
    model.fetchMore(model.index(1,0,i));
    model.fetchMore(model.index(2,0,i));
    model.fetchMore(model.index(3,0,i));
    model.fetchMore(model.index(4,0,i));
    model.fetchMore(model.index(5,0,i));
    qDebug() << "rowCount(i)" << model.data(i) << model.rowCount(i) << model.canFetchMore(i);
    i = model.index(0, 0, i);
    qDebug() << "rowCount(i)" << model.data(i) << model.rowCount(i) << model.canFetchMore(i);
    model.fetchMore(i);
    //qDebug() << "rowCount(i)" << model.data(i) << model.rowCount(i) << model.canFetchMore(i);

    QTreeView view;
    view.setUniformRowHeights(true);
    view.setModel(&model);
    view.expandAll();
    view.show();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("fsModel", &model);
    engine.load(QUrl(QStringLiteral("qrc:///demo.qml")));
    /**/
    return app.exec();
}