//
//  XnAnimCard.cpp
//
//  Created by LyneXiao on 16/7/19.
//
//

#include "XnAnimCard.h"

NS_CC_BEGIN


AnimCard* AnimCard::create(Texture2D * texture0, Texture2D * texture1)
{
    AnimCard *pAnimCard = new (std::nothrow) AnimCard();

    if (pAnimCard)
    {
        if (pAnimCard->initWithTexture(texture0, texture1))
        {
            pAnimCard->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pAnimCard);
        }
    }

    return pAnimCard;
}

AnimCard::AnimCard()
    : _texture0(nullptr)
    , _texture1(nullptr)
    , _texCoordinates(nullptr)
    , _vertices(nullptr)
    , _indices(nullptr)
    , _enabled(false)
    , _needDepthTestForBlit(true)
    , _verticesDirty(true)
	, _autoTurnOver(false)
	, _isAutoTurnning(false)
	, _autoTurnOverCompleted(false)
	, _hitTestCenterSizeScale(0)
	, _hitTestEdgeSizeScale(1.2f)
    , _roundRadius(40.0f)
	, _autoTurnSpeed(10.f)
	, _autoFixDistance(1.f)
	, _actionTweenCallfunc(nullptr)
{
	_ignoreAnchorPointForPosition = false;
	setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	_blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;

    _quadPoint   = Vec2::ZERO;
    _fingerPoint = Vec2::ZERO;
}

AnimCard::~AnimCard()
{
    CC_SAFE_RELEASE(_texture0);
    CC_SAFE_RELEASE(_texture1);

    CC_SAFE_FREE(_texCoordinates);
    CC_SAFE_FREE(_vertices);
    CC_SAFE_FREE(_indices);
}


bool AnimCard::initWithTexture(Texture2D * texture0, Texture2D * texture1)
{
    _texture0 = texture0;
    _texture1 = texture1;
    CC_SAFE_RETAIN(_texture0);
    CC_SAFE_RETAIN(_texture1);

    Size texSize = _texture0->getContentSize();
    setContentSize(texSize);

    // default shader program
    auto shaderProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE);
    setGLProgram(shaderProgram);

    return true;
}

void AnimCard::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	if (_verticesDirty || _transformDirty)
        updateVertexPoints();

    bool transformUpdated = flags & FLAGS_TRANSFORM_DIRTY;
    //_customCommand.init(_globalZOrder, transform, flags);
	_customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(AnimCard::onDraw, this, transform, transformUpdated);

    renderer->addCommand(&_customCommand);
}

void AnimCard::onDraw(const Mat4& transform, bool transformUpdated)
{
    beforeDraw();

    GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION
                           | GL::VERTEX_ATTRIB_FLAG_TEX_COORD);

    auto glprogram = getGLProgram();
    glprogram->use();
    glprogram->setUniformsForBuiltins(transform);


    GL::blendFunc( _blendFunc.src, _blendFunc.dst );

    GL::bindTexture2D(_texture0->getName());

    GL::bindTexture2DN(1,_texture1 ? _texture1->getName() : _texture0->getName());

    //
    // Attributes
    //

    // position
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, _vertices);
    
    // texCoords
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, _texCoordinates);
	
    glDrawElements(GL_TRIANGLES, _indicesCount, GL_UNSIGNED_SHORT, _indices);

    afterDraw();
}

void AnimCard::beforeDraw(void)
{
    if(_needDepthTestForBlit)
    {
        _oldDepthTestValue = glIsEnabled(GL_DEPTH_TEST) != GL_FALSE;
        GLboolean depthWriteMask;
        glGetBooleanv(GL_DEPTH_WRITEMASK, &depthWriteMask);
		_oldDepthWriteValue = depthWriteMask != GL_FALSE;
        CHECK_GL_ERROR_DEBUG();

        glEnable(GL_DEPTH_TEST);
//        RenderState::StateBlock::_defaultState->setDepthTest(true);

        glDepthMask(true);
//        RenderState::StateBlock::_defaultState->setDepthWrite(true);
    }
}

void AnimCard::afterDraw(void)
{
    if(_needDepthTestForBlit)
    {
        if(_oldDepthTestValue)
            glEnable(GL_DEPTH_TEST);
        else
            glDisable(GL_DEPTH_TEST);
//        RenderState::StateBlock::_defaultState->setDepthTest(_oldDepthTestValue);

        glDepthMask(_oldDepthWriteValue);
//        RenderState::StateBlock::_defaultState->setDepthWrite(_oldDepthWriteValue);
    }
}

void AnimCard::defaultVertexDatas(VerticesList& verticesList, IndicesList& indicesList)
{
    float width  = _contentSize.width;
    float height = _contentSize.height;

    // default vertices
	float z = _flippedX ^ _flippedY ? _roundRadius * 2 : 0.f;
    verticesList.push_back(VerticesData(0    , 0     , z, 0, 1));
    verticesList.push_back(VerticesData(width, 0     , z, 1, 1));
    verticesList.push_back(VerticesData(width, height, z, 1, 0));
    verticesList.push_back(VerticesData(0    , height, z, 0, 0));

    indicesList.resize(6);
    indicesList[0] = 0;
    indicesList[1] = 3;
    indicesList[2] = 2;
    indicesList[3] = 2;
    indicesList[4] = 1;
    indicesList[5] = 0;
}

float AnimCard::verticalVertexDatas(VerticesList& verticesList, IndicesList& indicesList, float x)
{
    float width    = _contentSize.width;
    float height   = _contentSize.height;
    if(x < width)          // 贴底部分
    {
        if(_quadPoint.x > 0)       //贴底在左侧
        {
            verticesList.push_back(VerticesData(0        , height , 0, 0            , 0));
            verticesList.push_back(VerticesData(0        , 0      , 0, 0            , 1));
            verticesList.push_back(VerticesData(width - x, height , 0, 1 - x / width, 0));
            verticesList.push_back(VerticesData(width - x, 0      , 0, 1 - x / width, 1));
        }
        else                         //贴底在右侧
        {
            verticesList.push_back(VerticesData(width, 0     , 0, 1        , 1));
            verticesList.push_back(VerticesData(width, height, 0, 1        , 0));
            verticesList.push_back(VerticesData(x    , 0     , 0, x / width, 1));
            verticesList.push_back(VerticesData(x    , height, 0, x / width, 0));
        }
    }

	if (_roundRadius > 0 && x > 0 && x < width + M_PI * _roundRadius)    // 圆弧部分
    {
        float da = MIN( M_PI / 6.f, 2.f / Director::getInstance()->getContentScaleFactor() / _roundRadius);
        float alpha = 0.f;
        while(alpha <= M_PI)
        {
            if(alpha > 0 || verticesList.empty())     //如果已有起点，则不增加第一条线
            {
                float dl = alpha * _roundRadius;
                float dp = sinf(alpha) * _roundRadius;
                float z  = (1 - cosf(alpha)) * _roundRadius;
            
                if(_quadPoint.x > 0)       //贴底在左侧
                {
                    verticesList.push_back(VerticesData(width - x + dp, height, z, 1 - (x - dl) / width, 0));
                    verticesList.push_back(VerticesData(width - x + dp, 0     , z, 1 - (x - dl) / width, 1));
                }
                else                         //贴底在右侧
                {
                    verticesList.push_back(VerticesData(x - dp, 0     , z, (x - dl) / width, 1));
                    verticesList.push_back(VerticesData(x - dp, height, z, (x - dl) / width, 0));
                }
            
				if (dl > x)                  //已超出渲染大小
				{
					break;
				}
            }
                       
            // 确保有一个值为pi/2的自增
            if(alpha < M_PI / 2 && M_PI / 2 - alpha <= da)
                alpha = M_PI / 2;
            else if(alpha < M_PI && M_PI - alpha <= da)
                alpha = M_PI;
            else
                alpha += da;
        }
    }

    if(x > M_PI * _roundRadius)        // 平行部分
    {
        if(_quadPoint.x > 0)       //贴底在左侧
        {
            if(verticesList.empty())     //如果已有起点，则不增加第一条线
            {
                verticesList.push_back(VerticesData(width - x, height, _roundRadius * 2, 1 - (x - M_PI * _roundRadius) / width, 0));
                verticesList.push_back(VerticesData(width - x, 0     , _roundRadius * 2, 1 - (x - M_PI * _roundRadius) / width, 1));
            }
            verticesList.push_back(VerticesData(width - x * 2 + _roundRadius * M_PI, height, _roundRadius * 2, 1, 0 ));
            verticesList.push_back(VerticesData(width - x * 2 + _roundRadius * M_PI, 0     , _roundRadius * 2, 1, 1 ));
        }
        else                         //贴底在右侧
        {
            if(verticesList.empty())     //如果已有起点，则不增加第一条线
            {
                verticesList.push_back(VerticesData(x, 0     , _roundRadius * 2, (x - M_PI * _roundRadius) / width, 1));
                verticesList.push_back(VerticesData(x, height, _roundRadius * 2, (x - M_PI * _roundRadius) / width, 0));
            }
            verticesList.push_back(VerticesData(x * 2 - _roundRadius * M_PI, 0     , _roundRadius * 2, 0, 1));
            verticesList.push_back(VerticesData(x * 2 - _roundRadius * M_PI, height, _roundRadius * 2, 0, 0));
        }
    }

    int numOfLine = (int)(verticesList.size() / 2);
    indicesList.resize((numOfLine - 1) * 6);
    for(int n = 0; n < numOfLine - 1; n++)
    {
        indicesList[6 * n + 0] = 2 * n + 1;
        indicesList[6 * n + 1] = 2 * n + 0;
        indicesList[6 * n + 2] = 2 * n + 2;
        indicesList[6 * n + 3] = 2 * n + 2;
        indicesList[6 * n + 4] = 2 * n + 3;
        indicesList[6 * n + 5] = 2 * n + 1;
    }

	return width;
}

float AnimCard::horizontalVertexDatas(VerticesList& verticesList, IndicesList& indicesList, float y)
{
    float width    = _contentSize.width;
    float height   = _contentSize.height;
    if(y < height)          // 贴底部分
    {
        if(_quadPoint.y > 0)       //贴底在下侧
        {
            verticesList.push_back(VerticesData(0    , 0          , 0, 0, 1          ));
            verticesList.push_back(VerticesData(width, 0          , 0, 1, 1          ));
            verticesList.push_back(VerticesData(0    , height - y , 0, 0, y / height ));
            verticesList.push_back(VerticesData(width, height - y , 0, 1, y / height ));
        }
        else                         //贴底在上侧
        {
            verticesList.push_back(VerticesData(width, height, 0, 1, 0              ));
            verticesList.push_back(VerticesData(0    , height, 0, 0, 0              ));
            verticesList.push_back(VerticesData(width, y     , 0, 1, 1 - y / height ));
            verticesList.push_back(VerticesData(0    , y     , 0, 0, 1 - y / height ));
        }
    }

	if (_roundRadius > 0 && y > 0 && y < height + M_PI * _roundRadius)    // 圆弧部分
    {
        float da = MIN( M_PI / 6.f, 2.f / Director::getInstance()->getContentScaleFactor() / _roundRadius);
        float alpha = 0.f;
        while(alpha <= M_PI)
        {
            if(alpha > 0 || verticesList.empty())     //如果已有起点，则不增加第一条线
            {
                float dl = alpha * _roundRadius;
                float dp = sinf(alpha) * _roundRadius;
                float z  = (1 - cosf(alpha)) * _roundRadius;
            
                if(_quadPoint.y > 0)         //贴底在下侧
                {
                    verticesList.push_back(VerticesData(0    , height - y + dp, z, 0, (y - dl) / height ));
                    verticesList.push_back(VerticesData(width, height - y + dp, z, 1, (y - dl) / height ));
                }
                else                         //贴底在上侧
                {
                    verticesList.push_back(VerticesData(width, y - dp, z, 1, 1 - (y - dl) / height));
                    verticesList.push_back(VerticesData(0    , y - dp, z, 0, 1 - (y - dl) / height));
                }

				if (dl > y)                  //已超出渲染大小
				{
					break;
				}
            }
            
            // 确保有一个值为pi/2的自增
            if(alpha < M_PI / 2 && M_PI / 2 - alpha <= da)
                alpha = M_PI / 2;
            else if(alpha < M_PI && M_PI - alpha <= da)
                alpha = M_PI;
            else
                alpha += da;
        }
    }

    if(y > M_PI * _roundRadius)        // 平行部分
    {
        if(_quadPoint.y > 0)       //贴底在下侧
        {
            if(verticesList.empty())     //如果已有起点，则不增加第一条线
            {
                verticesList.push_back(VerticesData(0    , height - y, _roundRadius * 2, 0, (y - M_PI * _roundRadius) / height ));
                verticesList.push_back(VerticesData(width, height - y, _roundRadius * 2, 1, (y - M_PI * _roundRadius) / height ));
            }
            verticesList.push_back(VerticesData(0    , height - y * 2 + _roundRadius * M_PI, _roundRadius * 2, 0, 0 ));
            verticesList.push_back(VerticesData(width, height - y * 2 + _roundRadius * M_PI, _roundRadius * 2, 1, 0 ));
        }
        else                         //贴底在上侧
        {
            if(verticesList.empty())     //如果已有起点，则不增加第一条线
            {
                verticesList.push_back(VerticesData(width, y, _roundRadius * 2, 1, 1 - (y - M_PI * _roundRadius) / height));
                verticesList.push_back(VerticesData(0    , y, _roundRadius * 2, 0, 1 - (y - M_PI * _roundRadius) / height));
            }
            verticesList.push_back(VerticesData(width, y * 2 - _roundRadius * M_PI, _roundRadius * 2, 1, 1));
            verticesList.push_back(VerticesData(0    , y * 2 - _roundRadius * M_PI, _roundRadius * 2, 0, 1));
        }
    }

    int numOfLine = (int)(verticesList.size() / 2);
    indicesList.resize((numOfLine - 1) * 6);
    for(int n = 0; n < numOfLine - 1; n++)
	{
		indicesList[6 * n + 0] = 2 * n + 1;
		indicesList[6 * n + 1] = 2 * n + 0;
		indicesList[6 * n + 2] = 2 * n + 2;
		indicesList[6 * n + 3] = 2 * n + 2;
		indicesList[6 * n + 4] = 2 * n + 3;
		indicesList[6 * n + 5] = 2 * n + 1;
    }

	return height;
}

float AnimCard::normalVertexDatas(VerticesList& verticesList, IndicesList& indicesList, float h, const Vec2& dirVec, const Vec2& offsetVec, const Vec2& referPoint)
{
    // 参数
    float width     = _contentSize.width;
    float height    = _contentSize.height;
    float referLen  = referPoint.length();
    Vec2  referVec  = referPoint / referLen;
    float k         = - referPoint.x / referPoint.y;                   // 斜率
    float referB    = referPoint.y - k * referPoint.x;                 // 参考直线偏移
    float b1        = referB * (h / referLen);                         // 折线偏移
    float b2        = referB * ((h - M_PI * _roundRadius) / referLen); // 平形部分截取线偏移
    // 对角线在方向上的投影长
    float oppositeH = referPoint.dot(Vec2(width, height)) / referLen;
    
    // 第一步，考虑到第二步平行四边形的做法，将贴底区域视为长方形与直角三角形的组合（如果长方形整块在区域外，则只有一个直角三角形）
    if(h < oppositeH)
    {
        std::vector<Vec2> points;
        if(fabs(k) >= height / width) // 斜率上扬，取折线与x轴和主y=height直线的交点作为斜边
        {
            float x1 = -b1 / k;            // 与x轴的交点Ｘ
            float x2 = (height - b1) / k;  // 与y=height的交点Ｘ
            if(x1 >= width)  //在框外
            {
                points.push_back(Vec2(x1, height));
            }
            else
            {
                points.push_back(Vec2(width, height));
                points.push_back(Vec2(width, 0     ));
            }
            points.push_back(Vec2(x1, 0     ));
            points.push_back(Vec2(x2, height));
        }
        else                          // 斜率下压，取折线与y轴和x=width直线的交点作为斜边
        {
            float y1 = b1;                 // 与y轴的交点Ｙ
            float y2 = k * width + b1;     // 与x=width的交点Ｙ
            if(y1 >= height)
            {
                points.push_back(Vec2(width, y1));
            }
            else
            {
				points.push_back(Vec2(0, height));
				points.push_back(Vec2(width, height));
			}
			points.push_back(Vec2(width, y2));
            points.push_back(Vec2(0    , y1));
        }
        
        for(int i = 0; i < (int)points.size(); i++)
        {
            const Vec2& p = points[i];
            float x = p.x * dirVec.x + offsetVec.x;
            float y = p.y * dirVec.y + offsetVec.y;
            verticesList.push_back(VerticesData(x,y,0,x/width,1-y/height));
			if (i >= 2)
			{
				if (dirVec.x * dirVec.y == 1)  // 无需翻转
				{
					// 顺时针
					indicesList.push_back(0);
					indicesList.push_back(i - 1);
					indicesList.push_back(i);
				}
				else
				{
					// 逆时针
					indicesList.push_back(0);
					indicesList.push_back(i);
					indicesList.push_back(i - 1);
				}
            }
        }
    }
    
    int startIndex = (int)verticesList.size();
    // 第二步，取到折线与Ｘ，Ｙ轴或x=width, y=height的交点，将圆上部分视为一个平行四边形，根据弧度进行过渡计算
	if (_roundRadius > 0 && h > 0 && h < oppositeH + M_PI * _roundRadius)
    {
        Vec2 start1, start2, ended1, ended2, metaVec;
        if(fabs(k) >= height / width) // 斜率上扬，取折线与x轴和y=height直线的交点作为斜边
        {
            // 与x轴的交点
            start1 = Vec2(-b1 / k, 0);
            ended1 = Vec2(-b2 / k, 0);
            // 与y=height的交点
            start2 = Vec2((height - b1) / k, height);
            ended2 = Vec2((height - b2) / k, height);
            
            metaVec = Vec2(-1, 0);
        }
        else                          // 斜率下压，取折线与y轴和x=width直线的交点作为斜边
		{
			// 与x=width的交点
			start1 = Vec2(width, k * width + b1);
			ended1 = Vec2(width, k * width + b2);
            // 与y轴的交点
            start2 = Vec2(0, b1);
            ended2 = Vec2(0, b2);
            
            metaVec = Vec2(0, -1);
        }

        Vec2 extendVec = start1 - ended1;
        float sinTheta = extendVec.dot(referPoint) / (extendVec.length() * referLen);
        float da = MIN( M_PI / 6.f, 2.f / Director::getInstance()->getContentScaleFactor() / _roundRadius);
        float alpha = 0.f;
        while(alpha <= M_PI)
        {
            if(alpha > 0 || verticesList.empty())     //如果已有起点，则不增加第一条线
            {
                float ds = alpha * _roundRadius;
                float dl = ds / sinTheta;
                float z  = (1 - cosf(alpha)) * _roundRadius;
                Vec2  dp = metaVec * dl + referVec * (ds - sinf(alpha) * _roundRadius);
                
                Vec2  p1 = dp + start1;
                Vec2  p2 = dp + start2;
                Vec2  t1 = start1 + metaVec * dl;
                Vec2  t2 = start2 + metaVec * dl;
                verticesList.push_back(VerticesData(p1.x * dirVec.x + offsetVec.x,
                                                    p1.y * dirVec.y + offsetVec.y,
                                                    z,
                                                    (t1.x * dirVec.x + offsetVec.x)/width,
                                                    1-(t1.y * dirVec.y + offsetVec.y)/height));
                verticesList.push_back(VerticesData(p2.x * dirVec.x + offsetVec.x,
                                                    p2.y * dirVec.y + offsetVec.y,
                                                    z,
                                                    (t2.x * dirVec.x + offsetVec.x)/width,
                                                    1-(t2.y * dirVec.y + offsetVec.y)/height));
                startIndex += 2;
                if(startIndex > 2)
				{
					if (dirVec.x * dirVec.y == 1)  // 无需翻转
					{
						// 顺时针
						indicesList.push_back(startIndex - 3);
						indicesList.push_back(startIndex - 4);
						indicesList.push_back(startIndex - 2);
						indicesList.push_back(startIndex - 2);
						indicesList.push_back(startIndex - 1);
						indicesList.push_back(startIndex - 3);
					}
					else
					{
						// 逆时针
						indicesList.push_back(startIndex - 4);
						indicesList.push_back(startIndex - 3);
						indicesList.push_back(startIndex - 1);
						indicesList.push_back(startIndex - 1);
						indicesList.push_back(startIndex - 2);
						indicesList.push_back(startIndex - 4);
					}
                }

				if (ds > h)                  //已超出渲染大小
				{
					break;
				}
            }
            
            // 确保有一个值为pi/2的自增
            if(alpha < M_PI / 2 && M_PI / 2 - alpha <= da)
                alpha = M_PI / 2;
            else if(alpha < M_PI && M_PI - alpha <= da)
                alpha = M_PI;
            else
                alpha += da;
        }
    }
    
    // 最后找到平形部分的多边形，与第一部的划分方式类似
    if(h > M_PI * _roundRadius)
    {
#define _DISTANCE_TO_LINE_(p, b) fabs((k * p.x - p.y + b) / powf(k * k + 1, 0.5f))
        if(fabs(k) >= height / width) // 斜率上扬，取折线与x轴和y=height直线的交点作为斜边
        {
            // 与x轴的交点
            Vec2 t1 = Vec2(-b2 / k, 0);
            // 与y=height的交点
            Vec2 t2 = Vec2((height - b2) / k, height);
            
            if(verticesList.size() <= 0)
            {
                Vec2 dp = referVec * _roundRadius * M_PI;
                Vec2 p1 = t1 + dp;
                Vec2 p2 = t2 + dp;
                
                verticesList.push_back(VerticesData(p1.x * dirVec.x + offsetVec.x,
                                                    p1.y * dirVec.y + offsetVec.y,
                                                    _roundRadius * 2,
                                                    (t1.x * dirVec.x + offsetVec.x)/width,
                                                    1-(t1.y * dirVec.y + offsetVec.y)/height));
                verticesList.push_back(VerticesData(p2.x * dirVec.x + offsetVec.x,
                                                    p2.y * dirVec.y + offsetVec.y,
                                                    _roundRadius * 2,
                                                    (t2.x * dirVec.x + offsetVec.x)/width,
                                                    1-(t2.y * dirVec.y + offsetVec.y)/height));
                
                startIndex += 2;
            }
            
            if(t2.x <= 0)        //三角形
            {
                Vec2 t3 = Vec2(t2.x, 0);
                Vec2 p3 = t3 + referVec * (_DISTANCE_TO_LINE_(t3, b1) * 2 - M_PI * _roundRadius);
                verticesList.push_back(VerticesData(p3.x * dirVec.x + offsetVec.x,
                                                    p3.y * dirVec.y + offsetVec.y,
                                                    _roundRadius * 2,
                                                    (t3.x * dirVec.x + offsetVec.x)/width,
                                                    1-(t3.y * dirVec.y + offsetVec.y)/height));

				if (dirVec.x * dirVec.y == 1)  // 无需翻转
				{
					// 顺时针
					indicesList.push_back(startIndex - 1);
					indicesList.push_back(startIndex - 2);
					indicesList.push_back(startIndex - 0);
				}
				else
				{
					// 逆时针
					indicesList.push_back(startIndex - 2);
					indicesList.push_back(startIndex - 1);
					indicesList.push_back(startIndex - 0);
				}
            }
            else                 //四边形
			{
				Vec2 t3 = Vec2(0, height);
                Vec2 t4 = Vec2(0, 0);
                Vec2 p3 = t3 + referVec * (_DISTANCE_TO_LINE_(t3, b1) * 2 - M_PI * _roundRadius);
                Vec2 p4 = t4 + referVec * (_DISTANCE_TO_LINE_(t4, b1) * 2 - M_PI * _roundRadius);
                verticesList.push_back(VerticesData(p3.x * dirVec.x + offsetVec.x,
                                                    p3.y * dirVec.y + offsetVec.y,
                                                    _roundRadius * 2,
                                                    (t3.x * dirVec.x + offsetVec.x)/width,
                                                    1-(t3.y * dirVec.y + offsetVec.y)/height));
                verticesList.push_back(VerticesData(p4.x * dirVec.x + offsetVec.x,
                                                    p4.y * dirVec.y + offsetVec.y,
                                                    _roundRadius * 2,
                                                    (t4.x * dirVec.x + offsetVec.x)/width,
                                                    1-(t4.y * dirVec.y + offsetVec.y)/height));

				startIndex += 2;
				if (dirVec.x * dirVec.y == 1)  // 无需翻转
				{
					// 顺时针
					indicesList.push_back(startIndex - 1);
					indicesList.push_back(startIndex - 2);
					indicesList.push_back(startIndex - 3);
					indicesList.push_back(startIndex - 3);
					indicesList.push_back(startIndex - 4);
					indicesList.push_back(startIndex - 1);
				}
				else
				{
					// 逆时针
					indicesList.push_back(startIndex - 1);
					indicesList.push_back(startIndex - 4);
					indicesList.push_back(startIndex - 3);
					indicesList.push_back(startIndex - 3);
					indicesList.push_back(startIndex - 2);
					indicesList.push_back(startIndex - 1);
				}
            }
        }
        else                          // 斜率下压，取折线与y轴和x=width直线的交点作为斜边
		{
			// 与x=width的交点
			Vec2 t1 = Vec2(width, k * width + b2);
			// 与y轴的交点
			Vec2 t2 = Vec2(0, b2);
            
            if(verticesList.size() <= 0)
			{
				Vec2 dp = referVec * _roundRadius * M_PI;
                Vec2 p1 = t1 + dp;
                Vec2 p2 = t2 + dp;
                
                verticesList.push_back(VerticesData(p1.x * dirVec.x + offsetVec.x,
                                                    p1.y * dirVec.y + offsetVec.y,
                                                    _roundRadius * 2,
                                                    (t1.x * dirVec.x + offsetVec.x)/width,
                                                    1-(t1.y * dirVec.y + offsetVec.y)/height));
                verticesList.push_back(VerticesData(p2.x * dirVec.x + offsetVec.x,
                                                    p2.y * dirVec.y + offsetVec.y,
                                                    _roundRadius * 2,
                                                    (t2.x * dirVec.x + offsetVec.x)/width,
                                                    1-(t2.y * dirVec.y + offsetVec.y)/height));
                
                startIndex += 2;
            }
            
            if(t1.y <= 0)        //三角形
            {
                Vec2 t3 = Vec2(0, t1.y);
                Vec2 p3 = t3 + referVec * (_DISTANCE_TO_LINE_(t3, b1) * 2 - M_PI * _roundRadius);
                verticesList.push_back(VerticesData(p3.x * dirVec.x + offsetVec.x,
                                                    p3.y * dirVec.y + offsetVec.y,
                                                    _roundRadius * 2,
                                                    (t3.x * dirVec.x + offsetVec.x)/width,
                                                    1-(t3.y * dirVec.y + offsetVec.y)/height));

				if (dirVec.x * dirVec.y == 1)  // 无需翻转
				{
					// 顺时针
					indicesList.push_back(startIndex - 1);
					indicesList.push_back(startIndex - 2);
					indicesList.push_back(startIndex - 0);
				}
				else
				{
					// 逆时针
					indicesList.push_back(startIndex - 2);
					indicesList.push_back(startIndex - 1);
					indicesList.push_back(startIndex - 0);
				}
            }
            else                 //四边形
			{
				Vec2 t3 = Vec2(0, 0);
				Vec2 t4 = Vec2(width, 0);
                Vec2 p3 = t3 + referVec * (_DISTANCE_TO_LINE_(t3, b1) * 2 - M_PI * _roundRadius);
                Vec2 p4 = t4 + referVec * (_DISTANCE_TO_LINE_(t4, b1) * 2 - M_PI * _roundRadius);
                verticesList.push_back(VerticesData(p3.x * dirVec.x + offsetVec.x,
                                                    p3.y * dirVec.y + offsetVec.y,
                                                    _roundRadius * 2,
                                                    (t3.x * dirVec.x + offsetVec.x)/width,
                                                    1-(t3.y * dirVec.y + offsetVec.y)/height));
                verticesList.push_back(VerticesData(p4.x * dirVec.x + offsetVec.x,
                                                    p4.y * dirVec.y + offsetVec.y,
                                                    _roundRadius * 2,
                                                    (t4.x * dirVec.x + offsetVec.x)/width,
                                                    1-(t4.y * dirVec.y + offsetVec.y)/height));

				startIndex += 2;
				if (dirVec.x * dirVec.y == 1)  // 无需翻转
				{
					// 顺时针
					indicesList.push_back(startIndex - 1);
					indicesList.push_back(startIndex - 2);
					indicesList.push_back(startIndex - 3);
					indicesList.push_back(startIndex - 3);
					indicesList.push_back(startIndex - 4);
					indicesList.push_back(startIndex - 1);
				}
				else
				{
					// 逆时针
					indicesList.push_back(startIndex - 1);
					indicesList.push_back(startIndex - 4);
					indicesList.push_back(startIndex - 3);
					indicesList.push_back(startIndex - 3);
					indicesList.push_back(startIndex - 2);
					indicesList.push_back(startIndex - 1);
				}
            }
        }
#undef _DISTANCE_TO_LINE_
    }
    
	return oppositeH;
}

// 二分法求x - sinx = v的x值（f(x)=x-sinx已知在0~pi间为单调递增
#define _MID_VALUE_DELTA_ (0.02f)
inline bool getMidValue(float& x, const float& v, float min, float minv, float max, float maxv)
{
	if (max == 0)
	{
		min = minv = 0;
		if (fabs(v - minv) <= _MID_VALUE_DELTA_)
		{
			x = min;
			return true;
		}
		max = maxv = M_PI;
		if (fabs(v - maxv) <= _MID_VALUE_DELTA_)
		{
			x = max;
			return true;
		}
	}
	float half  = (min + max) / 2;
	float halfv = half - sinf(half);
	x = half;
	if (fabs(v - halfv) <= _MID_VALUE_DELTA_)
	{
		return true;
	}
	if (minv < v && halfv > v)
		return getMidValue(x, v, min, minv, half, halfv);
	else if (halfv < v && maxv > v)
		return getMidValue(x, v, half, halfv, max, maxv);
	else
		return false;
	return true;
}
#undef _MID_VALUE_DELTA_

void AnimCard::computVertexDatas(VerticesList& verticesList, IndicesList& indicesList, Vec2& fixOffset)
{
    // 坐标系变换，翻转变换为折角为原点，折点在第一象限的坐标系（方便计算）
    Vec2 offsetVec   = Vec2::ZERO;
    Vec2 dirVec      = Vec2(1,1);
    if(_quadPoint.x > 0)
    {
        // 左右翻转
        dirVec.x    = -1;
        offsetVec.x = _contentSize.width;
    }
    if(_quadPoint.y > 0)
    {
        //上下翻转
        dirVec.y    = -1;
        offsetVec.y = _contentSize.height;
    }
    Vec2 referPoint = Vec2(_fingerPoint.x * dirVec.x, _fingerPoint.y * dirVec.y) + offsetVec;
    // 折点必需在第一象限
    if(referPoint.x < 0)
        referPoint.x = 0;
    if(referPoint.y < 0)
        referPoint.y = 0;
    
    //没有折叠，则使用默认顶点
    if(referPoint.equals(Vec2::ZERO))
    {
        defaultVertexDatas(verticesList, indicesList);
    }
    else
    {
		float maxBevelHeight = 0.0f;
        float distance = referPoint.distance(Vec2::ZERO);
        //先假设在圆弧外
		float bevelHeight = 0.0f;
		if (_roundRadius > 0 && distance <= _roundRadius * M_PI)     //在圆弧上
		{
			float alpha = 0;
			CCAssert(getMidValue(alpha, distance / _roundRadius, 0, 0, 0, 0), "What's wrong??");
			bevelHeight = alpha * _roundRadius;
		}
		else
		{
			bevelHeight = distance;   // 当翻过圆弧部分后，圆弧位置不再变化，直到完全翻过
			float delta = bevelHeight - M_PI * _roundRadius;
			Vec2 vec = referPoint * (delta / distance);
			fixOffset.x -= dirVec.x * vec.x;
			fixOffset.y -= dirVec.y * vec.y;
		}

        if(referPoint.x == 0) // line: y = n
        {
			maxBevelHeight = horizontalVertexDatas(verticesList, indicesList, bevelHeight);
        }
        else if(referPoint.y == 0) // line: x = n
        {
			maxBevelHeight = verticalVertexDatas(verticesList, indicesList, bevelHeight);
        }
        else
        {
			maxBevelHeight = normalVertexDatas(verticesList, indicesList, bevelHeight, dirVec, offsetVec, referPoint);
        }

		if (bevelHeight > maxBevelHeight)
		{
			float delta = bevelHeight - maxBevelHeight;
			Vec2 vec = referPoint * (delta / distance);
			fixOffset.x -= dirVec.x * vec.x;
			fixOffset.y -= dirVec.y * vec.y;
		}

		if (_autoTurnSpeed > 0.f && (_autoTurnOver || bevelHeight >= maxBevelHeight * _autoFixDistance))
		{
			if (!_autoTurnOverCompleted && !_isAutoTurnning)
			{
				float width = _contentSize.width;
				float height = _contentSize.height;
				_autoTurnTargetPoint = Vec2::ZERO;
#if 0
				if (referPoint.x > 2 * referPoint.y)
				{
					_autoTurnTargetPoint.x = width + M_PI * _roundRadius + 10.f;
				}
				else if (referPoint.y > 2 * referPoint.x)
				{
					_autoTurnTargetPoint.y = height + M_PI * _roundRadius + 10.f;
				}
				else
				{
					_autoTurnTargetPoint.x = width + M_PI * _roundRadius;
					_autoTurnTargetPoint.y = width + M_PI * _roundRadius;
				}
#else
				if (referPoint.x > referPoint.y)
				{
					_autoTurnTargetPoint.x = width + M_PI * _roundRadius + 10.f;
				}
				else
				{
					_autoTurnTargetPoint.y = height + M_PI * _roundRadius + 10.f;
				}
#endif
				_autoTurnTargetPoint.x = _autoTurnTargetPoint.x * dirVec.x + offsetVec.x;
				_autoTurnTargetPoint.y = _autoTurnTargetPoint.y * dirVec.y + offsetVec.y;

				_isAutoTurnning = true;

				if (_ccEventCallback)
					_ccEventCallback(this, static_cast<int>(EventType::ANIMCARD_AUTOTURN_START));
			}

			if (_isAutoTurnning && !_fingerPoint.equals(_autoTurnTargetPoint))
			{
				Vec2 deltaVec  = _autoTurnTargetPoint - _fingerPoint;
				float deltaLen = deltaVec.length();
				if (deltaLen <= _autoTurnSpeed)
				{
					_fingerPoint = _autoTurnTargetPoint;
				}
				else
				{
					_fingerPoint.x += deltaVec.x * (_autoTurnSpeed / deltaLen);
					_fingerPoint.y += deltaVec.y * (_autoTurnSpeed / deltaLen);
				}
				_verticesDirty = true;
			}
			else
			{
				if (_isAutoTurnning)
				{
					_isAutoTurnning = false;
					_autoTurnOverCompleted = true;

					if (_ccEventCallback)
						_ccEventCallback(this, static_cast<int>(EventType::ANIMCARD_AUTOTURN_ENDED));
				}
			}
		}
    }
}

void AnimCard::updateVertexPoints(void)
{
    // clear
    CC_SAFE_FREE(_vertices);
    CC_SAFE_FREE(_texCoordinates);
    CC_SAFE_FREE(_indices);

	_verticesDirty = false;

    // compute
    VerticesList _verticesList;
    IndicesList  _indicesList;
	Vec2         _fixOffset = Vec2::ZERO;
    computVertexDatas(_verticesList, _indicesList, _fixOffset);

    // copy
    size_t numOfPoints = _verticesList.size();
    size_t numOfIndice = _indicesList.size();
    _vertices = malloc(numOfPoints * sizeof(Vec3));
    _texCoordinates = malloc(numOfPoints * sizeof(Vec2));
    _indices = (GLushort*)malloc(numOfIndice * sizeof(GLushort));

    GLfloat  *vertArray = (GLfloat*)_vertices;
    GLfloat  *texArray  = (GLfloat*)_texCoordinates;
	GLushort *idxArray  = _indices;
    for(size_t i = 0; i < numOfPoints; i++)
    {
        const VerticesData& data = _verticesList[i];
		vertArray[i * 3 + 0] = (GLfloat)(data.position.x + _fixOffset.x);
		vertArray[i * 3 + 1] = (GLfloat)(data.position.y + _fixOffset.y);
        vertArray[i * 3 + 2] = (GLfloat)data.position.z;
        texArray[i * 2 + 0]  = (GLfloat)data.texCoord.x;
        texArray[i * 2 + 1]  = (GLfloat)data.texCoord.y;
	}

    for(size_t j = 0; j < numOfIndice; j++)
    {
        idxArray[j] = (GLushort)_indicesList[j];
    }

    _indicesCount =	 (GLsizei)numOfIndice;
}

bool AnimCard::hitTest(const Vec2 &pt)
{
	Vec2 nsp = convertToNodeSpace(pt);
	Rect bb;
	bb.size   = _contentSize * _hitTestCenterSizeScale;
	bb.origin = (_contentSize - bb.size) * 0.5f;
	if (bb.containsPoint(nsp))
	{
		return false;
	}

	bb.size = _contentSize * _hitTestEdgeSizeScale;
	bb.origin = (_contentSize - bb.size) * 0.5f;
	if (bb.containsPoint(nsp))
	{
		return true;
	}
	return false;
}

void AnimCard::setTurnPoint(const Vec2& quadPoint, const Vec2& fingerPoint)
{
	if (!quadPoint.equals(_quadPoint))
	{
		_quadPoint = quadPoint;
		_verticesDirty = true;
	}

	if (!fingerPoint.equals(_fingerPoint))
	{
		_fingerPoint = fingerPoint;
		_verticesDirty = true;
	}
}

void AnimCard::clearTurnPoint(void)
{
	this->setTurnPoint(Vec2::ZERO, Vec2::ZERO);
}

void AnimCard::setAutoTurnOver(bool isAuto)
{
	if (isAuto != _autoTurnOver)
	{
		_autoTurnOver = isAuto;
		if (isAuto)
		{
			_verticesDirty = true;
		}
	}
}

void AnimCard::addActionTweenCallfunc(const ccAnimCardTweenCallback& tweenCallfunc)
{
	_actionTweenCallfunc = tweenCallfunc;
}

void AnimCard::updateTweenAction(float value, const std::string& key)
{
	if (_actionTweenCallfunc)
	{
		_actionTweenCallfunc(this, value, key);
	}
}

void AnimCard::setRoundRadius(float radius)
{
	_roundRadius = radius;
	_verticesDirty = true;
}

NS_CC_END
