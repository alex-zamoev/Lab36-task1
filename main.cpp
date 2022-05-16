#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QSlider>

class myWidget : public QWidget{
public:
    myWidget(QWidget *parent);
    void paintEvent(QPaintEvent *e) override;
    QSize minimumSizeHint() const override;
public slots:
    void setYellow();
    void setGreen();
    void setRed();
private:
    QPixmap mYellow;
    QPixmap mGreen;
    QPixmap mRed;
    QPixmap mCurr;
};

myWidget::myWidget(QWidget *parent) {
    setParent(parent);
    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    mGreen = QPixmap("c:\\Users\\alex\\CLionProjects\\Lab36\\task1\\green.png");
    mYellow = QPixmap("c:\\Users\\alex\\CLionProjects\\Lab36\\task1\\yellow.png");
    mRed = QPixmap("c:\\Users\\alex\\CLionProjects\\Lab36\\task1\\red.png");
    mCurr = mYellow;
    setGeometry(mCurr.rect());
}
void myWidget::paintEvent(QPaintEvent *e) {
    QPainter p(this);
    p.drawPixmap(e->rect(), mCurr);
}

QSize myWidget::minimumSizeHint() const {
    return QSize(100,100);
}

void myWidget::setYellow() {
    mCurr = mYellow;
    update();
}
void myWidget::setGreen() {
    mCurr = mGreen;
    update();
}
void myWidget::setRed() {
    mCurr = mRed;
    update();
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget *window = new QWidget;
    auto slider = new QSlider(Qt::Horizontal, window);
    slider->setMinimum(0);
    slider->setMaximum(99);
    auto *layout = new QVBoxLayout(window);
    myWidget *myCircle = new myWidget(window);

    layout->addWidget(myCircle);
    layout->addWidget(slider);
    QObject::connect(slider, &QSlider::valueChanged, [slider, myCircle](int newValue)
    {
        if(newValue > 0 && newValue <= 33)
            myCircle->setYellow();
        else if(newValue > 34 && newValue <= 66)
            myCircle->setGreen();
        else if(newValue > 67 && newValue <= 99)
            myCircle->setRed();
    });
    window->setFixedSize(200,200);
    window->move(1000,400);
    window->show();

    return app.exec();
}
