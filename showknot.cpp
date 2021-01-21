#include "showknot.h"
#include "tree.h"
#include "renderarea.h"
#include "knotpos.h"
#include "calculateposition.h"
#include <QGridLayout>
#include <QComboBox>
#include <QScreen>
#include <QApplication>
#include <iostream>

/**
 * @brief Konstruktor zum Starten eines Fensters.
 * @param tree
 *          Übergebener Baum.
 */
ShowKnot::ShowKnot(struct TreeNode* tree)
{
    if(tree == nullptr)
        throw "Der übergebene Baum darf nicht 'null' sein!";

    scene = new RenderArea(deltaX, deltaY, this);

    penChanged();
    brushChanged();

    knotpos *test0 = nullptr;
    test0 = calculateposition::positionen_eintragen(tree, deltaX, deltaY, scene);
    test0->setSquare();
    test0->setColor(new QColor(Qt::yellow));
    scene->addKnot(test0);

    setWindowTitle(tr("QTTree"));

    setCentralWidget(scene->view);

    QRectF qrf = scene->sceneRect();
    QSize rec = qApp->screens()[0]->size();

    int barHeight = QApplication::style()->pixelMetric(QStyle::PM_TitleBarHeight);
    int frameWidth = QApplication::style()->pixelMetric(QStyle::PM_DefaultFrameWidth) * 2;
    int scrollBar = QApplication::style()->pixelMetric(QStyle::PM_ScrollBarExtent);

    int width = qrf.width() + frameWidth + scrollBar; if(width > rec.width()) width = rec.width();
    int height = qrf.height() + frameWidth + scrollBar; if(height > rec.height() - barHeight)  height = rec.height() - barHeight;
    resize(width, height);
    setMinimumSize(width / 4, height / 4);

    int x = rec.width() - width; if(x != 0) x /= 2; if(x < 0) x = 0;
    int y = rec.height() - (height + barHeight); if(y != 0) y /= 2; if(y < 0) y = 0;
    move(x, y);
}

ShowKnot::ShowKnot(BTreeNode *tree)
{
    scene = new RenderArea(deltaX, deltaY, this);

    penChanged();
    brushChanged();

    knotpos *test0 = nullptr;
    test0 = calculateposition::positionen_eintragen(tree, deltaX, deltaY, scene);
    test0->setSquare();
    test0->setColor(new QColor(Qt::yellow));
    scene->addKnot(test0);

    setWindowTitle(tr("QTTree"));

    setCentralWidget(scene->view);

    QRectF qrf = scene->sceneRect();
    QSize rec = qApp->screens()[0]->size();

    int barHeight = QApplication::style()->pixelMetric(QStyle::PM_TitleBarHeight);
    int frameWidth = QApplication::style()->pixelMetric(QStyle::PM_DefaultFrameWidth) * 2;
    int scrollBar = QApplication::style()->pixelMetric(QStyle::PM_ScrollBarExtent);

    int width = qrf.width() + frameWidth + scrollBar; if(width > rec.width()) width = rec.width();
    int height = qrf.height() + frameWidth + scrollBar; if(height > rec.height() - barHeight)  height = rec.height() - barHeight;
    resize(width, height);
    setMinimumSize(width / 4, height / 4);

    int x = rec.width() - width; if(x != 0) x /= 2; if(x < 0) x = 0;
    int y = rec.height() - (height + barHeight); if(y != 0) y /= 2; if(y < 0) y = 0;
    move(x, y);
}

ShowKnot::ShowKnot(struct RBTreeNode *tree, RBTreeNode *nil)
{
    scene = new RenderArea(deltaX, deltaY, this);

    penChanged();
    brushChanged();

    knotpos *test0 = nullptr;
    test0 = calculateposition::positionen_eintragen(tree, deltaX, deltaY, scene, nil);
    test0->setSquare();
    scene->addKnot(test0);

    setWindowTitle(tr("QTTree"));

    setCentralWidget(scene->view);

    QRectF qrf = scene->sceneRect();
    QSize rec = qApp->screens()[0]->size();

    int barHeight = QApplication::style()->pixelMetric(QStyle::PM_TitleBarHeight);
    int frameWidth = QApplication::style()->pixelMetric(QStyle::PM_DefaultFrameWidth) * 2;
    int scrollBar = QApplication::style()->pixelMetric(QStyle::PM_ScrollBarExtent);

    int width = qrf.width() + frameWidth + scrollBar; if(width > rec.width()) width = rec.width();
    int height = qrf.height() + frameWidth + scrollBar; if(height > rec.height() - barHeight)  height = rec.height() - barHeight;
    resize(width, height);
    setMinimumSize(width / 4, height / 4);

    int x = rec.width() - width; if(x != 0) x /= 2; if(x < 0) x = 0;
    int y = rec.height() - (height + barHeight); if(y != 0) y /= 2; if(y < 0) y = 0;
    move(x, y);
}


/**
 * @brief Methode zur Rückgabe des Zeichenobjektes.
 * @return RenderArea (Zeichenobjekt)
 */
RenderArea* ShowKnot::getRenderArea(){
    return scene;
}

/**
 * @brief Methode zum Setzen des Standard-Pens
 */
void ShowKnot::penChanged()
{
    Qt::PenStyle style = Qt::PenStyle(Qt::SolidLine);
    Qt::PenCapStyle cap = Qt::PenCapStyle(Qt::FlatCap);
    Qt::PenJoinStyle join = Qt::PenJoinStyle(Qt::MiterJoin);
    scene->setPen(QPen(Qt::black, 2, style, cap, join));
}

/**
 * @brief Methode zum Setzen des Standard-Brushs.
 */
void ShowKnot::brushChanged()
{
   Qt::BrushStyle style = Qt::BrushStyle(Qt::SolidPattern);
   scene->setBrush(QBrush(Qt::gray, style));
}


/**
 * @brief Static-Function zum Erstellen eines Objektes.
 * @param tree
 *          Baum zum Anzeigen
 * @return RenderArea-Objekt
 */
ShowKnot* ShowKnot::display(struct TreeNode* tree){
    if(tree == nullptr)
        throw "Der übergebene Baum darf nicht 'null' sein!";
    ShowKnot* s = new ShowKnot(tree);
    s->show();
    return s;
};

ShowKnot* ShowKnot::display(BTreeNode *tree){
    ShowKnot* s = new ShowKnot(tree);
    s->show();
    return s;
};

ShowKnot* ShowKnot::display(RBTreeNode *tree, RBTreeNode *nil){
    ShowKnot* s = new ShowKnot(tree, nil);
    s->show();
    return s;
};
