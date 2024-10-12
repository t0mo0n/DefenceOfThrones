## 功能需求

### 1 . **防御塔功能**

   - 玩家可以在特定位置花费金币放置防御塔。
   - 玩家可以拆除已经放置的防御塔, 返还一定的金币
   - 防御塔能够自动攻击进入其射程的敌人。(发射各种子弹)
   - 防御塔在没有找到敌人攻击的时候, 会自动攻击地图内的障碍物
   - 防御塔可以使用金币升级，提升攻击力和攻击范围。

## 类设计

### 7. **TowerFrame (防御塔基类)**

- **全局**
    - 希望全局控制者能维护一个敌人队列，每次从队列中取出一个敌人给防御塔攻击
- **主要成员变量:**
    - `towerSize`:防御塔本体的大小(静态)
    - `int projectType`//投掷物的种类
    - `int towertype`//防御塔的种类
    - `int level`//防御塔现在的等级

    - `int attackRange`:攻击范围
    - `int attackSpeed`:攻击速度
    - `int buyCost`:购买花费
    - `int sellPrice;`:出售价格
    - `QGraphicsItem* target`:攻击的敌人

    - `QString picDir`:图片位置
    - `QVector<int> upgradeFee`:升级费用
    - `QVector<Projectile*> projectileList`:投掷物列表
    - `QPointF TowerCentral;`//相对于场景的坐标

- **主要方法:**
    - `explicit TowerFrame(QPoint pos_=QPoint(0,0),int type=0);`:防御塔基类构造函数
    - `virtual void attack()=0;`:攻击
    - `void findEnemy();`//跟踪并且瞄准敌人

    - `int getBuyCost(){return buy_cost;};`:获得购买的价格
    - `int getSellPrice(){return sellPrice;};`:获得出售的价格
    - `int getUpdateCost()`:获得升级需要的价格
    - `void setTarget(QGraphicsItem* target_out=nullptr);`:给防御塔设置敌人
    - `void resetTarget();`:(不需要手动调用,已经自动实现)如果敌人死了,调用这个方法把这个防御塔和投掷物的敌人置空

    - `void paint(QPainter * painterconst,const QStyleOptionGraphicsItem *option, QWidget *widget)override;`//画出防御塔
    - `QRectF boundingRect() const override;`
    - `void mousePressEvent(QGraphicsSceneMouseEvent *event) override ;`
    - `void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;`:右键防御塔会出现升级和出售



- **public slots:**
    - `virtual void Upgrade()=0;`//升级植物,界面设计者要根据现有的钱和updatecost比较获得是否可行,别忘了扣钱
    - `void Sell();`//出售植物并将植物删除

### 7.1 **Archer(弓箭手)** 
  - **主要接口**
    - `explicit Archer(QPoint pos_=QPoint(0,0));`:弓箭手的位置
    - `void attack()override;`:调用弓箭手攻击,每次调用都会自动向敌人发出炮弹

### 7.2 **Tower2 (增益塔)**


### 7.3 **Tower3 (减速塔)**
  - 单伤害
  - 群伤 


### 7.4 **Tower4 (传送塔)**
  - 把敌人传送会起点重新行走路线



### 9. **Projectile (投射物基类)**

- **功能:** 定义防御塔发射的子弹或魔法攻击。
- **主要成员变量:**
    - `int speed;`:子弹的速度
    - `int damage;`:子弹的伤害
    - `QString src;`:投掷物的图片
    - `QGraphicsItem* enemys;`:子弹的目标
    - `QPointF delta;`:子弹位移的偏移量
    - `QTimer* moveTimer ;`:子弹移动的计时器
    - `QPointF towerCor;`:子弹所属防御塔中心坐标
    - `qreal tattackRange;`:塔的攻击范围



- **主要方法:**
    - `explicit Projectile(QPointF pos,QPointF Tower_c,qreal attack_range);`
    - `void setTarget(QGraphicsItem* Enemy=nullptr);`:设置子弹的攻击敌人
    - `void moveToEneny();`:自动向敌人移动
    - `void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;`
    - `QRectF boundingRect() const override;`
    - `static qreal pix_size;`:子弹的大小
    - `void outOfRange();`:删除超过攻击范围的子弹
    - `void destroy();`:子弹销毁的信号