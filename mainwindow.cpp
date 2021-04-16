#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QShortcut>
#include <QScreen>
#include <QTimer>


MainWindow::MainWindow(Params &params, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Configure borders, size and so on
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus);
    setParent(nullptr);
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_TranslucentBackground, true);
//    setAttribute(Qt::WA_ShowWithoutActivating, true);


    // Close on ESCAPE
    auto s = new QShortcut(QKeySequence("Escape"), this);
    connect(s, &QShortcut::activated, [this]()
    {
        close();
    });


    // Add labels
    const int selection = params.getUInt("selection", 0);
    const int numOptions = params.has("options") ? params.len("options") : 0;
    QList<QString> options;

    for (int i=0;i!=numOptions;++i)
    {
        QString text = params.getStringAt("options", i).c_str();
        QLabel *l = new QLabel(text);

        Qt::Alignment a(Qt::AlignmentFlag::AlignHCenter);
        l->setAlignment(a);

        if (i == selection)
            l->setStyleSheet("color: #ffffff; background-color: #00000000;");
        else
            l->setStyleSheet("color: #7e9da7; background-color: #00000000;");

        ui->verticalLayout->addWidget(l);
    }


    // Configure border and size
    this->setStyleSheet(
        "border: 0px;"
        "border-radius: 10px;"
        "background-color: #e60a1b1f;"
        "padding-left: 30px;"
        "padding-right: 30px;"
    );

    ui->centralwidget->show(); // This will force centralWidget to recalculate its size
    QSize dialogSize = ui->centralwidget->size();
    this->resize(dialogSize);


    // Position window
    const string position = params.getString("position", "top");
    QSize screenSize = QGuiApplication::screens()[0]->size();

    if (position == "center")
    {
        const int x = (screenSize.width() - dialogSize.width()) / 2;
        const int y = (screenSize.height() - dialogSize.height()) / 2;
        this->move(x, y);
    }

    else if (position == "top")
    {
        const int x = (screenSize.width() - dialogSize.width()) / 2;
        const int y = 0;
        this->move(x, y);
    }

    else if (position == "bottom")
    {
        const int x = (screenSize.width() - dialogSize.width()) / 2;
        const int y = screenSize.height() - dialogSize.height();
        this->move(x, y);
    }

    else
    {
        print("Unknown position:", position);
    }


    // Set the timer to close the notification
    const uint timer = params.getUInt("timer", 2000);
    QTimer::singleShot(timer, this, [this](){
        this->close();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

