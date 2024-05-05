#include "Ground.h"

namespace gs {

Ground::Ground(ArgumentStream &stream) : Object(stream) {

    constexpr int num = 1000;

    {
        Qt3DRender::QGeometryRenderer *renderer = new Qt3DRender::QGeometryRenderer(Object::getRoot());
        Qt3DRender::QGeometry *geometry = new Qt3DRender::QGeometry(Object::getRoot());

        Qt3DRender::QBuffer *vertexBuffer = new Qt3DRender::QBuffer(geometry);
        QByteArray vertexBufferData;
        vertexBufferData.resize(4*num * 3 * sizeof(float));
        float *rawVertexArray = reinterpret_cast<float*>(vertexBufferData.data());
        for(int i=0; i<num+1; i++) {
            if(i!=num/2) {
                *rawVertexArray++ = -num/2;
                *rawVertexArray++ = i - num/2;
                *rawVertexArray++ = 0;
                *rawVertexArray++ = num/2;
                *rawVertexArray++ = i - num/2;
                *rawVertexArray++ = 0;
            }
        }
        for(int i=0; i<num+1; i++) {
            if(i!=num/2) {
                *rawVertexArray++ = i - num/2;
                *rawVertexArray++ = -num/2;
                *rawVertexArray++ = 0;
                *rawVertexArray++ = i - num/2;
                *rawVertexArray++ = num/2;
                *rawVertexArray++ = 0;
            }
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

    {
        Qt3DRender::QGeometryRenderer *renderer = new Qt3DRender::QGeometryRenderer(Object::getRoot());
        Qt3DRender::QGeometry *geometry = new Qt3DRender::QGeometry(Object::getRoot());

        Qt3DRender::QBuffer *vertexBuffer = new Qt3DRender::QBuffer(geometry);
        QByteArray vertexBufferData;
        vertexBufferData.resize(6 * sizeof(float));
        float *rawVertexArray = reinterpret_cast<float*>(vertexBufferData.data());
        *rawVertexArray++ = -num/2;
        *rawVertexArray++ = 0;
        *rawVertexArray++ = 0;
        *rawVertexArray++ = num/2;
        *rawVertexArray++ = 0;
        *rawVertexArray++ = 0;
        vertexBuffer->setData(vertexBufferData);

        Qt3DRender::QAttribute *positionAttribute = new Qt3DRender::QAttribute();
        positionAttribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());
        positionAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
        positionAttribute->setVertexSize(3);
        positionAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
        positionAttribute->setBuffer(vertexBuffer);
        positionAttribute->setByteOffset(0);
        positionAttribute->setByteStride(3 * sizeof(float));
        positionAttribute->setCount(2);
        geometry->addAttribute(positionAttribute);

        renderer->setGeometry(geometry);
        renderer->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);

        Qt3DCore::QEntity *axis = new Qt3DCore::QEntity(Object::getRoot());
        material_x = new Qt3DExtras::QPhongMaterial();

        material_x->setAmbient(Qt::darkRed);

        axis->addComponent(material_x);
        axis->addComponent(renderer);
    }

    {
        Qt3DRender::QGeometryRenderer *renderer = new Qt3DRender::QGeometryRenderer(Object::getRoot());
        Qt3DRender::QGeometry *geometry = new Qt3DRender::QGeometry(Object::getRoot());

        Qt3DRender::QBuffer *vertexBuffer = new Qt3DRender::QBuffer(geometry);
        QByteArray vertexBufferData;
        vertexBufferData.resize(6 * sizeof(float));
        float *rawVertexArray = reinterpret_cast<float*>(vertexBufferData.data());
        *rawVertexArray++ = 0;
        *rawVertexArray++ = -num/2;
        *rawVertexArray++ = 0;
        *rawVertexArray++ = 0;
        *rawVertexArray++ = num/2;
        *rawVertexArray++ = 0;
        vertexBuffer->setData(vertexBufferData);

        Qt3DRender::QAttribute *positionAttribute = new Qt3DRender::QAttribute();
        positionAttribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());
        positionAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
        positionAttribute->setVertexSize(3);
        positionAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
        positionAttribute->setBuffer(vertexBuffer);
        positionAttribute->setByteOffset(0);
        positionAttribute->setByteStride(3 * sizeof(float));
        positionAttribute->setCount(2);
        geometry->addAttribute(positionAttribute);

        renderer->setGeometry(geometry);
        renderer->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);

        Qt3DCore::QEntity *axis = new Qt3DCore::QEntity(Object::getRoot());
        material_y = new Qt3DExtras::QPhongMaterial();

        material_y->setAmbient(Qt::darkGreen);

        axis->addComponent(material_y);
        axis->addComponent(renderer);
    }

    setColors(QColor(128, 128, 128), Qt::darkRed, Qt::darkGreen);
}

void Ground::setColors(const QColor grid, const QColor x, const QColor y) {
    material->setDiffuse(grid);
    material_x->setDiffuse(x);
    material_y->setDiffuse(y);

    material->setAmbient(grid);
    material_x->setAmbient(x);
    material_y->setAmbient(y);
}

}
