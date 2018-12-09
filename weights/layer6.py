from nnUtils import *

##IMAGES are divided by 255 before input. Floats from 0 to 1.
model = Sequential([
    SpatialConvolution(32,3,3, padding='SAME', bias=True,name='conv1'),
    SpatialMaxPooling(2,2,2,2),
    ReLU(),

    SpatialConvolution(64,3,3, padding='SAME', bias=True,name='conv2'),
    SpatialMaxPooling(2,2,2,2),
    ReLU(),

    SpatialConvolution(64,3,3, padding='SAME', bias=True,name='conv3'),
    SpatialMaxPooling(2,2,2,2),
    ReLU(),

    SpatialConvolution(128,3,3, padding='SAME', bias=True,name='conv4'),
    SpatialMaxPooling(2,2,2,2),
    ReLU(),

    SpatialConvolution(128,3,3, padding='SAME', bias=True,name='conv5'),
    SpatialMaxPooling(2,2,2,2),
    ReLU(),

    SpatialConvolution(256,3,3, padding='SAME', bias=True,name='conv6'),
    SpatialMaxPooling(2,2,2,2),
    ReLU(),

    Affine(1024, bias=True),
    ReLU(),
    Affine(14, bias=True)
])
