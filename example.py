import socket
import json
import numpy
import time

soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
soc.connect(('localhost', 8080))

def write(msg):
    soc.send(json.dumps(msg).encode())

write({'command': 'clear'})

write({
    'command': 'config',
    'theme': 'dark',
    'camera': 'orbit',
})

write({
    'command': 'create',
    'path': 'obj1',
    'geometry': {
        'shape': 'sphere',
        'radius': 0.25,
    },
    'material': {
        'color': [255, 0, 0],
    },
})

write({
    'command': 'create',
    'path': 'obj2',
    'geometry': {
        'shape': 'cylinder',
        'radius': 0.25,
        'height': 0.25,
    },
    'material': {
        'color': [0, 255, 0],
    },
})

write({
    'command': 'create',
    'path': 'obj2/obj3',
    'geometry': {
        'shape': 'cuboid',
        'size': [0.25, 0.25, 0.25],
    },
    'material': {
        'color': [255, 0, 255],
    },
    'transform': {
        'translation': [1, 0, 0],
    },
})

write({
    'command': 'create',
    'path': 'obj2/obj3/obj4',
    'geometry': {
        'shape': 'cuboid',
        'size': [0.25, 0.25, 0.25],
    },
    'material': {
        'color': [255, 255, 0],
    },
    'transform': {
        'translation': [1, 0, 0],
    },
})

t = 0

while True:
    t +=0.01

    write({
        'command': 'update',
        'path': 'obj2',
        'transform': {
            'translation': [numpy.sin(t), 0, 0],
        },
    })

    write({
        'command': 'update',
        'path': 'obj2/obj3',
        'transform': {
            'rpy': [0, 0, 100*t],
        },
    })

    time.sleep(0.01)
