//
//  XnAnimCard.h
//
//  Created by LyneXiao on 16/7/19.
//
//

#ifndef XnAnimCard_h
#define XnAnimCard_h

#include "cocos2d.h"
#include "ui/UIWidget.h"

NS_CC_BEGIN


class AnimCard: public ui::Widget, public ActionTweenDelegate
{
protected:
    struct VerticesData
    {
        Vec3      position;
        Vec2      texCoord;

        VerticesData(float x, float y, float z, float tx, float ty)
        {
            position.x = x;
            position.y = y;
            position.z = z;
            texCoord.x = tx;
            texCoord.y = ty;
        }
    };

public:
	enum class EventType
	{
		ANIMCARD_AUTOTURN_START,
		ANIMCARD_AUTOTURN_ENDED,
	};

	typedef std::function<void(Ref*, float, const std::string&)> ccAnimCardTweenCallback;

    static AnimCard * create(Texture2D * texture0, Texture2D * texture1 = nullptr);

    void setNeedDepthTest(bool value) { _needDepthTestForBlit = value; };

    void setRoundRadius(float radius);

	void setHitTestCenterSizeScale(float centerScale) { _hitTestCenterSizeScale = centerScale; };
	float getHitTestCenterSizeScale(void) { return _hitTestCenterSizeScale; };
	void setHitTestEdgeSizeScale(float rageScale) { _hitTestEdgeSizeScale = rageScale; };
	float getHitTEstEdgeSizeScale(void) { return _hitTestEdgeSizeScale; };

	void setTurnPoint(const Vec2& quadPoint, const Vec2& fingerPoint);
	void clearTurnPoint(void);

	bool isAutoTurnning() { return _isAutoTurnning; };
	void setAutoTurnOver(bool isAuto);
	void setAutoTurnSpeed(float speed) { _autoTurnSpeed = speed; };
	void setAutoFixDistance(float fixd) { _autoFixDistance = fixd; };

	void addActionTweenCallfunc(const ccAnimCardTweenCallback& tweenCallfunc);
public:
    ~AnimCard();

    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags) override;

	virtual bool hitTest(const Vec2 &pt) override;

	virtual void updateTweenAction(float value, const std::string& key) override;
protected:
    AnimCard();

    void onDraw(const Mat4& transform, bool transformUpdated);

    void beforeDraw(void);
    void afterDraw(void);

    bool initWithTexture(Texture2D * texture0, Texture2D * texture1);

    typedef std::vector<VerticesData> VerticesList;
    typedef std::vector<int>          IndicesList;
    // 没有折叠时的顶点数据
    void defaultVertexDatas(VerticesList& verticesList, IndicesList& indicesList);
    // 垂直折叠时的顶点数据
    float verticalVertexDatas(VerticesList& verticesList, IndicesList& indicesList, float x);
    // 水平折叠时的顶点数据
	float horizontalVertexDatas(VerticesList& verticesList, IndicesList& indicesList, float y);
    // 斜边折叠时的顶点数据
	float normalVertexDatas(VerticesList& verticesList, IndicesList& indicesList, float h, const Vec2& dirVec, const Vec2& offsetVec, const Vec2& referPoint);

	// 当没有帖底部分时返回true
    void computVertexDatas(VerticesList& verticesList, IndicesList& indicesList, Vec2& fixOffset);

    void updateVertexPoints(void);
protected:
    Texture2D *_texture0;
    Texture2D *_texture1;

    GLvoid *_texCoordinates;
    GLvoid *_vertices;
    GLushort *_indices;
    bool _needDepthTestForBlit;
    bool _oldDepthTestValue;
    bool _oldDepthWriteValue;

    GLsizei _indicesCount;

    BlendFunc     _blendFunc;
    CustomCommand _customCommand;

	bool  _isAutoTurnning;
	bool  _autoTurnOverCompleted;
	bool  _autoTurnOver;
	float _autoTurnSpeed;
	float _autoFixDistance;

    float _roundRadius;

	float _hitTestCenterSizeScale;
	float _hitTestEdgeSizeScale;

    bool  _verticesDirty;

    bool _enabled;
	EventListenerTouchOneByOne* _touchListener;

    Vec2 _quadPoint;         // 被折起来的顶点
    Vec2 _fingerPoint;       // 折角折到坐标
	Vec2 _touchPoint;        // 触摸点
	Vec2 _autoTurnTargetPoint;  // 自动翻牌目标点

	ccAnimCardTweenCallback _actionTweenCallfunc;
};

NS_CC_END

#endif /* XnAnimCard_h */
