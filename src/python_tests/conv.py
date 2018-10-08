import tensorflow as tf
import numpy as np
import scipy.signal as ss

sess = tf.InteractiveSession()

arr = np.ones((6,6))
arr[3,3] = 4; arr[4,4] = 4;
arr[0,2] = 0
arr0 = arr.reshape((1,6,6,1))
f = np.array([[1,1,0],[0,0,0],[0,2,0]] )
f0 = f.reshape((3,3,1,1))

convolved = tf.nn.conv2d(arr0, f0, strides=[1, 1, 1, 1], padding="SAME")

c1 = ss.convolve(arr, f,'same')
c2 = ss.convolve(arr, np.flipud(f), 'same')
c3 = ss.convolve(arr, np.fliplr(f), 'same')
c4 = ss.convolve(arr, np.fliplr(np.flipud(f)), 'same')
c5 = ss.convolve(arr, np.flipud(np.fliplr(f)), 'same')

c0 = convolved.eval().reshape(6,6)

print c0
print c1
#print c2
#print c3
#print c4
#print c5
#print c6
from IPython import embed
embed()
