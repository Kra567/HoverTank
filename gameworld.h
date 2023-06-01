#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include "bodycollider.h"
#include "curvecollider.h"
#include "damagecollider.h"
#include "activity.h"
#include <QObject>
#include "body.h"
#include "gametimer.h"
#include "platform.h"
#include "graphs.h"

/*
class GameObject : public Activity {

};
*/

class GameObject : public Activity{
private:
    int draw_priority_ = 0;
    Q_OBJECT
public:
    virtual void paint(QPainter&)  = 0;
    void setDrawPriority(int prior);
    int getDrawPriority();
    //virtual ObjectType getType() = 0;

};



class Bullet : public GameObject {
    Q_OBJECT
public:
    /*
    QPointF startPos;
    QPointF startVel;
    double mass;
    double radius;
    int startHealth;
    double damage;
    */
    int startHealth;
    int damage;
private:
    Body* body_;
    BodyAssociated* obj_ = nullptr;

public:
    Bullet();
    Bullet(Body* bbody,int health,double damage);
    Body* getBody();
    void setBody(Body*);
    void setObject(BodyAssociated*);
    void paint(QPainter&) override;
};



class Weapon {
private:
    std::vector<double> angles_;
    double velocity_;
    int damage_;
    int health_;
    double mass_;
    double radius_;
public:
    Weapon();
    Weapon(const std::vector<double> angles,double velocity,double mass,double radius,int damage,int health);
    std::vector<Bullet> spamBullets(const QPointF& pos,const QPointF& vector);
    double getRadius();



};



class Hero : public GameObject{
    Q_OBJECT
private:
    QPointF way_ = QPoint(0,1);
    BodyAssociated* obj_ = nullptr;
    std::vector<Weapon> weapons_;
    int current_weapon_ = 0;

public:
    Hero();
    void setObject(BodyAssociated*);
    void setWeapons(const std::vector<Weapon>&);
    QPointF getVector();
    void paint(QPainter&);
    void setWay(const QPointF&);
    void addVelocity(const QPointF&);
    BodyAssociated* getBody();
public slots:
    void shoot();
signals:
    void spamBullets(const std::vector<Bullet>&);


};

class Wall : public GameObject{
private:
    QImage img_ = QImage();
    PolynomCurve* curve_ = nullptr;
    CurveAssociated* obj_ = nullptr;
public:
    Wall();
    Wall(const PolynomCurve& curve);
    PolynomCurve *getCurve();
    void setObject(CurveAssociated*);
    void paint(QPainter&) override;
    void setImage(const QImage&);
};

class Enemy : public GameObject{
    Q_OBJECT
private:
    //Body* body_;
    Body* body_ = nullptr;
    BodyAssociated* obj_ = nullptr;
    int damage_;
    double velocity_;
    int health_;
    QPointF startPos_;
    StableForce* force_ = new StableForce();
public:
    Enemy();
    Enemy(Body*,int health,int damage,double velocity);
    void setAssoc(BodyAssociated*);
    BodyAssociated* getAssoc();
    Body* getBody();
    double getVelocity();
    int getDamage();
    int getHealth();
    StableForce* getForce();
    void paint(QPainter&) override;



};

using InnerEnemySpammer = std::function<void(Enemy*)>;

class EnemyManager : public QObject{
    Q_OBJECT
private:
    //Hero* hero_;
    GraphMap* graphmap_;
    std::vector<Enemy*> enemies_;
    InnerEnemySpammer spammer_;

public:
    EnemyManager();
    EnemyManager(GraphMap*,InnerEnemySpammer);
    EnemyManager& operator=(const EnemyManager& man);
    void spamEnemy(const Enemy&);
    void spamCascade(double acc);
public slots:
    void filterActiveEnemies();
    void renewVels(Hero*);


};


class GameWorld : public QObject
{
    Q_OBJECT
public:
    double limit = 250;
    double push = 250;
    double dx = 0;

    LimitForce* left = new LimitForce(limit,QPointF(-push,0));
    LimitForce* right = new LimitForce(limit,QPointF(push,0));
    LimitForce* up = new LimitForce(limit,QPointF(0,-push));
    LimitForce* down = new LimitForce(limit,QPointF(0,push));
private:
    EnemyManager enemymanager_;
    GraphMap map_ = GraphMap(QPoint(0,0),QPoint(1536+1,864+1),25);
    BodyCollider bodycollider_ = BodyCollider();
    CurveCollider curvecollider_ = CurveCollider();
    DamageCollider damagecollider_ = DamageCollider();
    std::vector<GameObject*> objects_;
    VoidForce* Void = new VoidForce();
    FrictionForce* friction = new FrictionForce();
    GameTimer* timer = new GameTimer();
    Hero* hero_ = nullptr;

    CurveCollider inviseBarriers_ = CurveCollider();

    //QObject::connect(timer,SIGNAL(timeout()),&bodycollider_,SLOT(collision()));
public:
    GameWorld();
    //void start(QPaintDevice*);
    void spamEnemyPtr(Enemy*);
    void spamEnemy(const Enemy&);
    void spamWall(const Wall&);
    void paint(QPainter& painter);
    Hero* getHero();
    GameTimer *getGameTimer();
    void spamHero(const QPointF&,const std::vector<Weapon>&);

public slots:
    void spamBullet(const Bullet&);
    void spamBullets(const std::vector<Bullet>&);

};

#endif // GAMEWORLD_H
