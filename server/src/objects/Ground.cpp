#include "Ground.h"

namespace gs {

Ground::Ground(Qt3DCore::QEntity *root) : Object(root) {

    Qt3DRender::QGeometryRenderer *renderer = new Qt3DRender::QGeometryRenderer(root);
    Qt3DRender::QGeometry *geometry = new Qt3DRender::QGeometry(root);

    const int len = 100000;
    const int num = 10000;

    Qt3DRender::QBuffer *vertexBuffer = new Qt3DRender::QBuffer(geometry);
    QByteArray vertexBufferData;
    vertexBufferData.resize(4*num * 3 * sizeof(float));
    float *rawVertexArray = reinterpret_cast<float*>(vertexBufferData.data());
    for(int i=0; i<num; i++) {
        rawVertexArray[6*i + 0] = -len;
        rawVertexArray[6*i + 1] = 0.0f;
        rawVertexArray[6*i + 2] = 10*(i - num/2);
        rawVertexArray[6*i + 3] = len;
        rawVertexArray[6*i + 4] = 0.0f;
        rawVertexArray[6*i + 5] = 10*(i - num/2);
    }
    for(int i=0; i<num; i++) {
        rawVertexArray[6*num + 6*i + 0] = 10*(i - num/2);
        rawVertexArray[6*num + 6*i + 1] = 0.0f;
        rawVertexArray[6*num + 6*i + 2] = -len;
        rawVertexArray[6*num + 6*i + 3] = 10*(i - num/2);
        rawVertexArray[6*num + 6*i + 4] = 0.0f;
        rawVertexArray[6*num + 6*i + 5] = len;
    }
    vertexBuffer->setData(vertexBufferData);

    Qt3DRender::QAttribute *positionAttribute = new Qt3DRender::QAttribute();
    positionAttribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());
    positionAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
    positionAttribute->setVertexSize(3);
    positionAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    positionAttribute->setBuffer(vertexBuffer);
    positionAttribute->setByteOffset(0);
    positionAttribute->setByteStride(3 * sizeof(float));
    positionAttribute->setCount(4*num);
    geometry->addAttribute(positionAttribute);

    renderer->setGeometry(geometry);
    renderer->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);

    entity->addComponent(renderer);
}

}
