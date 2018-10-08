import tensorflow as tf
import numpy as np
import scipy.signal as ss
from skimage.measure import block_reduce

sess = tf.InteractiveSession()

layers = np.load('arr.npz')['arr_0']

images = np.load('train_images.npy')
img = images[7]
import pdb
pdb.set_trace()
for img in images[:10]:
    img = img.reshape((1,28,28,1))
    out1 = []

    out0 = ss.correlate(img[0], layers[0][:,:,:,0], 'same')
    for i in range(32):
        out = ss.correlate(img[0], layers[0][:,:,:,i], 'same')
        out += layers[1][i]
        out1.append(out)
    out1 = np.concatenate(out1, axis=-1)
    pool1 = block_reduce(out1, block_size=(2,2,1), func=np.max)

    out2 = []
    for i in range(64):
        out = np.zeros((14,14))
        for j in range(32):
            out += ss.correlate(pool1[:,:,j], layers[2][:,:,j,i], 'same')
        out += layers[3][i]
        out2.append(out)
    out2 = np.stack(out2, axis=2)
    pool2 = block_reduce(out2, block_size=(2,2,1), func=np.max)

    flat = pool2.flatten()
    fc1 = np.matmul(flat, layers[4]) + layers[5]
    fc1 = fc1 * (fc1 > 0)
    fc2 = np.matmul(fc1, layers[6]) + layers[7]
    print np.argmax(fc2)


    #r1 = tf.nn.conv2d(img, layers[0], [1,1,1,1], 'SAME').eval()
    #for i in range(32):
    #    r1[:,:,:,i] += layers[1][i]
    #p1 = tf.nn.max_pool(r1, [1,2,2,1], [1,2,2,1], 'SAME').eval()
    #r2 = tf.nn.conv2d(p1, layers[2], [1,1,1,1], 'SAME').eval()

    #for i in range(64):
    #    r2[:,:,:,i] += layers[3][i]
    #p2 = tf.nn.max_pool(r2, [1,2,2,1], [1,2,2,1], 'SAME').eval()





from IPython import embed
embed()
