#include "gameworld.h"
#include "body.h"
#include "DamagableObject.h"
#include <QPainter>
#include <QTransform>
#include "platform.h"
#include <QPainter>
#include <functional>
#include <QRect>
#include <algorithm>

void GameWorld::spamEnemyPtr(Enemy * enemy)
{
    qDebug() << "Enemy Spammed";
    enemy->getBody()->connectForce(Void);
    enemy->getBody()->connectForce(enemy->getForce());
    enemy->getBody()->connectForce(friction);
    enemy->getBody()->connectGameTimer(timer);
    bodycollider_.addBody(enemy->getBody());
    curvecollider_.addBody(enemy->getBody());
    damagecollider_.addObject(enemy->getAssoc());
    objects_.push_back(enemy);

}

void GameWorld::spamEnemy(const Enemy & enem)
{
    enemymanager_.spamEnemy(enem);

}

GameWorld::GameWorld()
{

    //QObject::connect(timer,SIGNAL(timeout()),&damagecollider_,SLOT(collision()));
    //QObject::connect(timer,&GameTimer::timeout,enemymanager_,[&](){filterActive<Enemy>(enemymanager_->getEnemies());})
    inviseBarriers_.addCurve(new PolynomCurve({QPointF(200,60),QPointF(60,300)}));
    inviseBarriers_.addCurve(new PolynomCurve({QPointF(1330,60),QPointF(1440,300)}));
    inviseBarriers_.addCurve(new PolynomCurve({QPointF(1440,500),QPointF(1300,760)}));
    inviseBarriers_.addCurve(new PolynomCurve({QPointF(200,760),QPointF(60,500)}));


    QObject::connect(timer,&GameTimer::timeout,&inviseBarriers_,&CurveCollider::collision);
    QObject::connect(timer,SIGNAL(timeout()),&curvecollider_,SLOT(collision()));
    QObject::connect(timer,SIGNAL(timeoutInterval(double)),&bodycollider_,SLOT(collision(double)));
    QObject::connect(timer,&GameTimer::timeout,&enemymanager_,[&](){enemymanager_.renewVels(hero_);});
    QObject::connect(timer,SIGNAL(timeout()),&damagecollider_,SLOT(collision()));
    //QObject::connect(timer,SIGNAL(timeout()),&curvecollider_,SLOT(collision()));
    //QObject::connect(timer,SIGNAL(timeout()),&damagecollider_,SLOT(collision()));
    QObject::connect(timer,&GameTimer::timeout,&enemymanager_,&EnemyManager::filterActiveEnemies);
    QObject::connect(timer,&GameTimer::timeout,this,[&](){filterActive<GameObject>(objects_);});
    //enemymanager_ = EnemyManager([&](Enemy* enem){spamEnemyPtr(enem);});
    enemymanager_ =  EnemyManager(&map_,[&](Enemy* enem){spamEnemyPtr(enem);});
    //enemymanager_.spamCascade(200);
    QObject::connect(timer,&GameTimer::timeout,this,[&](){dx += 0.1;});
    QObject::connect(timer,&GameTimer::timeout,this,[&](){
        if (timer->ticks % int(500 - dx)== 0){
            enemymanager_.spamCascade(200);
        }
    });
    timer->setInterval(15);
    //timer->start();

}



void GameWorld::spamBullet(const Bullet & bull_)
{
    Bullet* bull = new Bullet(bull_);
    bull->setDrawPriority(1);
    BodyAssociated* dmg = new BodyAssociated(bull->getBody(),ObjectType::BULLET,bull->startHealth,
                                             {
                                                 //{ObjectType::HERO,bull->damage},
                                                 {ObjectType::ENEMY,bull->damage}});
    curvecollider_.addBody(bull->getBody());
    damagecollider_.addObject(dmg);
    bodycollider_.addBody(bull->getBody()); // testing
    bull->setObject(dmg);
    bull->getBody()->connectGameTimer(timer);
    objects_.push_back(bull);

}

void GameWorld::spamBullets(const std::vector<Bullet> & bulls)
{
    for (auto& bull : bulls){
        spamBullet(bull);
    }
}

void GameWorld::spamHero(const QPointF & pos,const std::vector<Weapon>& weapons)
{
    Hero* hero = new Hero();
    hero->setDrawPriority(7);
    hero_ = hero;
    hero->setWeapons(weapons);
    Body* body = new Body(pos,50,30);
    body->connectForce(Void);
    body->connectForce(friction);
    body->connectGameTimer(timer);
    // sides
    body->connectForce(up);
    body->connectForce(down);
    body->connectForce(left);
    body->connectForce(right);
    //invis
    inviseBarriers_.addBody(body );
    // other
    BodyAssociated* assoc = new BodyAssociated(body,ObjectType::HERO,200,{{ObjectType::BULLET,INT_MAX/100}});
    bodycollider_.addBody(body);
    damagecollider_.addObject(assoc);
    curvecollider_.addBody(body);
    hero->setObject(assoc);
    objects_.push_back(hero);
    QObject::connect(hero,&Hero::spamBullets,this,&GameWorld::spamBullets);

}

void GameWorld::spamWall(const Wall & wall_)
{
    Wall* wall = new Wall(wall_);
    CurveAssociated* obj = new CurveAssociated(wall->getCurve(),ObjectType::WALL,1,{{ObjectType::BULLET,1}});
    curvecollider_.addCurve(wall->getCurve());
    damagecollider_.addObject(obj);
    objects_.push_back(wall);
    map_.bakeMap(*wall->getCurve());


}

void GameWorld::paint(QPainter &painter)
{
    //curvecollider_.debugPaint(painter);
    //map_.paint(painter);
    //map_.paint(painter);
    QPointF beg = QPointF(250,250);
    //painter.setBrush(Qt::green);
    //painter.setPen(Qt::green);
    //painter.drawEllipse(beg,7,7);
    //std::vector<QPoint> way = map_.shortestWay(beg,hero_->getBody()->getPosition());

    //painter.setBrush(Qt::green);
    //painter.setPen(Qt::green);

    //painter.setBrush(Qt::red);
    //painter.setPen(Qt::red);
    //qDebug() << way;


    /*
    if (way.size() >= 2){
        //qDebug() << "S";
        for (int i = 0;i < way.size()-1;i++){
            //qDebug() << way[i];
            painter.drawEllipse(way[i],3,3);
            painter.drawLine(way[i],way[i+1]);
        }
    }
    */


    //objects_.sort(objects_,[&](GameObject* a,GameObject* b){return a->getDrawPriority() < b->getDrawPriority();});
    //
    //painter.setPen();

    std::sort(objects_.begin(),objects_.end(),
              [&](GameObject* a,GameObject* b){return a->getDrawPriority() < b->getDrawPriority();});
    for (auto obj : objects_){
        obj->paint(painter);
    }
    painter.setPen(Qt::red);
    PolynomCurve({QPointF(200,60),QPointF(60,300)}).paint(painter);
    PolynomCurve({QPointF(1330,60),QPointF(1440,300)}).paint(painter);
    PolynomCurve({QPointF(1440,500),QPointF(1300,760)}).paint(painter );
    PolynomCurve({QPointF(200,760),QPointF(60,500)}).paint(painter);
    //map_.paint(painter);
    //map_.paint(painter);

}

Hero *GameWorld::getHero()
{
    return hero_;
}

GameTimer *GameWorld::getGameTimer()
{
    return timer;
}

Bullet::Bullet()
{

}

Bullet::Bullet(Body* bbody,int health, double bdamage)
{
    //mass = bmass;
    //radius = bradius;
    body_ = bbody;
    damage = bdamage;
    startHealth = health;

}

Body* Bullet::getBody()
{
    return body_;
}

void Bullet::setBody(Body * body)
{
    body_ = body;
}

void Bullet::setObject(BodyAssociated * obj)
{
    obj_ = obj;
    QObject::connect(obj_,&Activity::disactivated,this,&Activity::disactivate);
}

void Bullet::paint(QPainter & painter)
{
    //painter.setPen(QColorConstants::Svg::purple);
    //painter.setBrush(QColorConstants::Svg::purple);
    //painter.drawEllipse(obj_->getPosition(),obj_->getRadius(),obj_->getRadius());
    QImage bullet(":/BulletSprites/IMG/BULLET.png");
    QPointF vec_ = QPointF(obj_->getRadius(),obj_->getRadius());

    painter.drawImage(QRect(
                           (obj_->getPosition() - vec_).toPoint(),
                           (obj_->getPosition() + vec_).toPoint()
                           ),bullet);
}

Wall::Wall()
{

}

Wall::Wall(const PolynomCurve& a)
{
    curve_ = new PolynomCurve(a);
}

PolynomCurve *Wall::getCurve()
{
    return curve_;
}

void Wall::setObject(CurveAssociated * obj)
{
    obj_ = obj;
    QObject::connect(obj_,&Activity::disactivated,this,&Activity::disactivate);
}

void Wall::paint(QPainter & painter)
{
    //painter.setBrush(Qt::red);
    //painter.setPen(Qt::red);
    painter.setPen(Qt::TransparentMode);
    curve_->paintWithImage(painter,img_ );
}

void Wall::setImage(const QImage & img)
{
    img_ = img;
}

/*Hero::Hero(const QPointF &)
{
    way_ =
}
*/

Hero::Hero()
{
    QObject::connect(this,&Activity::disactivated,this,[&](){delete this;});
}

void Hero::setObject(BodyAssociated * obj)
{
    obj_ = obj;
    QObject::connect(obj_,&Activity::disactivated,this,&Activity::disactivate);

}

void Hero::setWeapons(const std::vector<Weapon> & weapons)
{
    weapons_ = weapons;
}

QPointF Hero::getVector()
{
    return 1.0001*Platform::normalize(way_ - obj_->getPosition()) * (obj_->getRadius()+weapons_[current_weapon_].getRadius());
}

void Hero::paint(QPainter & painter)
{
    //base
    QImage tank_base(":/HeroSprites/IMG/Image2.png");
    QImage tank_head(":/HeroSprites/IMG/Image7.png");
    // line
    QPointF vec = getVector();
    QPointF pos = obj_->getPosition();
    painter.setBrush(Qt::green);
    painter.setPen(Qt::green);
    painter.drawLine(pos,pos + 3.5*vec);

    // ball
    QPointF vec_ = QPointF(obj_->getRadius(),obj_->getRadius());

    painter.drawImage(QRect(
                           (obj_->getPosition() - vec_).toPoint(),
                           (obj_->getPosition() + vec_).toPoint()
                           ),tank_base);

    //QPointF vec_ = QPointF(obj_->getRadius(),obj_->getRadius());


    double angle = 0;
    if (vec != QPointF(0,0)){
        angle = PolynomCurve::radianAngle(vec);
    }



    double coeff = 2.45;
    painter.translate(+obj_->getPosition());
    painter.scale(coeff,coeff);
    painter.rotate((angle-M_PI/2)/(M_PI)*180);
    painter.drawImage(QRect(-vec_.toPoint(),vec_.toPoint()),tank_head);
    painter.rotate((-angle+M_PI/2)/(M_PI)*180);
    painter.scale(1/coeff,1/coeff);
    painter.translate(-obj_->getPosition());

    //double coeff = (1+abs(cos(8*angle)))/2;
    //double coeff = 1;
    //painter.drawPixmap(QRect(
    //                       (obj_->getPosition() - 3/coeff*vec_).toPoint(),
    //                       (obj_->getPosition() + 3/coeff*vec_).toPoint()
    //                       ),tank_head.transformed(QTransform().rotateRadians(angle-M_PI/2)));




    // ball0

    //painter.drawPixmap()
    //painter.setBrush(Qt::blue);
    //painter.setPen(Qt::blue);
    //painter.drawEllipse(pos,obj_->getRadius(),obj_->getRadius());

}

void Hero::setWay(const QPointF & way)
{
    way_ = way;
}

void Hero::addVelocity(const QPointF & vel)
{
    obj_->getBody()->addVelocity(vel);
}

BodyAssociated *Hero::getBody()
{
    return obj_;
}

void Hero::shoot()
{
    emit spamBullets(weapons_[current_weapon_].spamBullets(obj_->getPosition(),getVector()));
}

Weapon::Weapon(const std::vector<double> angles, double velocity, double mass,double radius,int damage, int health)
{

    angles_ = angles;
    velocity_ = velocity;
    damage_ = damage;
    health_ = health;
    mass_ = mass;
    radius_ = radius;
}

std::vector<Bullet> Weapon::spamBullets(const QPointF &pos, const QPointF &vector)
{
    std::vector<Bullet> res;
    for (auto angle : angles_){
        QPointF way = QTransform().rotateRadians(angle).map(vector);
        //QPointF vel = QTransform().rotateRadians(angle).map(velocity_*vector);
        Body* body = new Body(pos+way,mass_,radius_);
        //QPointF vel = QTransform().rotateRadians(angle).map(velocity_*vector);
        body->setVelocity(velocity_*Platform::normalize(way));
        Bullet bull = Bullet(body,health_,damage_);
        res.push_back(bull);
    }
    return res;
}

double Weapon::getRadius()
{
    return radius_;
}


Enemy::Enemy()
{

}

Enemy::Enemy(Body* body,int health,int damage, double velocity)
{
    damage_ = damage;
    velocity_ = velocity;
    body_ = body;
    health_ = health;


}

void Enemy::setAssoc(BodyAssociated * obj)
{
    obj_ = obj;
    QObject::connect(obj_,&Activity::disactivated,this,&Activity::disactivate);
}

BodyAssociated* Enemy::getAssoc()
{
    return obj_;

}

Body *Enemy::getBody()
{
    return body_;
}

double Enemy::getVelocity()
{
    return velocity_;
}

int Enemy::getDamage()
{
    return damage_;
}

int Enemy::getHealth()
{
    return health_;
}

StableForce *Enemy::getForce()
{
    return force_;
}

void Enemy::paint(QPainter & painter)
{
    //qDebug() << force_->getAcceleration();
    //painter.setBrush(Qt::red);
    //painter.setPen(Qt::red);
    //painter.drawEllipse(body_->getPosition(),body_->getRadius(),body_->getRadius());
    QImage enemy_image(":/EnemySprites/IMG/uebok.png");
    QPointF vec_ = QPointF(obj_->getRadius(),obj_->getRadius());

    painter.drawImage(QRect(
                           (obj_->getPosition() - vec_).toPoint(),
                           (obj_->getPosition() + vec_).toPoint()
                           ),enemy_image);
}

EnemyManager::EnemyManager()
{

}

EnemyManager::EnemyManager(GraphMap* graphmap,InnerEnemySpammer spammer)
{
    spammer_ = spammer;
    graphmap_ = graphmap;
}

EnemyManager &EnemyManager::operator=(const EnemyManager &man)
{
    enemies_ = man.enemies_;
    spammer_ = man.spammer_;
    graphmap_ = man.graphmap_;
    return *this;
}

void EnemyManager::spamEnemy(const Enemy & enem)
{
    Enemy* enemy = new Enemy(enem);
    enemy->setDrawPriority(5);
    //qDebug() << "S" << (enemy == nullptr);
    //qDebug() << "S";
    BodyAssociated* assoc = new BodyAssociated(enemy->getBody(),ObjectType::ENEMY
                                               ,enemy->getHealth(),
                                               {{ObjectType::HERO,enemy->getDamage()},
                                                 {ObjectType::BULLET,INT_MAX/100}});
    enemy->setAssoc(assoc);
    enemies_.push_back(enemy);
    spammer_(enemy);
    //spammer_(enemy);

}

void EnemyManager::spamCascade(double acc)
{
    for (auto p : {QPointF(50,60),QPointF(1450,60),QPointF(50,760), QPointF(1450,760)}){
        spamEnemy(Enemy(new Body(p,170,25),30,10,acc));
    }
}

void EnemyManager::filterActiveEnemies()
{
    filterActive(enemies_);
}

void EnemyManager::renewVels(Hero* hero)
{
    if (hero == nullptr){
        return;
    }
    std::vector<QPointF> poses;
    for (auto enem : enemies_){
        poses.push_back(enem->getBody()->getPosition());
    }
    std::vector<QPointF> vecs = graphmap_->getVectors(hero->getBody()->getPosition(),poses);
    for (int i = 0;i < vecs.size();i++){
        enemies_[i]->getForce()->setAcceleration(enemies_[i]->getVelocity() * Platform::normalize(vecs[i]));
    }
}

void GameObject::setDrawPriority(int prior)
{
    draw_priority_ = prior;
}

int GameObject::getDrawPriority()
{
    return draw_priority_;
}

