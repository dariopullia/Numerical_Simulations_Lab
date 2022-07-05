from itertools import dropwhile
import tensorflow as tf
from tensorflow import keras
import os

import sys
import numpy as np
import matplotlib.pyplot as plt
seed=2
np.random.seed(seed) # fix random seed
tf.random.set_random_seed(seed)

from tensorflow.keras.datasets import mnist


epochs=7 #di base ho 7, modifica temporanea
opt='Adagrad'
NConvLayers=int(sys.argv[1])
NDeepLayers=int(sys.argv[2])
Drop=float(sys.argv[3])
NMaxPool=int(sys.argv[4])
NAvgPool=int(sys.argv[5])

# input image dimensions
img_rows, img_cols = 28, 28 # number of pixels 
# output
num_classes = 10 # 10 digits

# the data, split between train and test sets
(X_train, Y_train), (X_test, Y_test) = mnist.load_data()

# reshape data, it could depend on tensorflow.keras backend
#X_train = X_train.reshape(X_train.shape[0], img_rows*img_cols)
#X_test = X_test.reshape(X_test.shape[0], img_rows*img_cols)
X_train = X_train.reshape(-1,28, 28, 1)
X_test = X_test.reshape(-1,28, 28, 1)
# cast floats to single precision
X_train = X_train.astype('float32')

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout

def create_CNN():
    # instantiate model
    model = Sequential()
    input_shape=(28,28,1)
    # add first convolutional layer with 10 filters (dimensionality of output space)
    model.add(keras.layers.Conv2D(10, kernel_size=(5, 5),
                     activation='relu',
                     input_shape=input_shape))
    for i in range(NConvLayers):
        model.add(keras.layers.Conv2D(5, kernel_size=(3, 3),
                     activation='relu',
                     input_shape=input_shape))

    for i in range(NMaxPool):
        model.add(keras.layers.MaxPooling2D(pool_size=(2, 2), strides=None, padding="same",))
    for i in range(NAvgPool):
        model.add(keras.layers.AveragePooling2D(pool_size=(2, 2), strides=None, padding="same",))


    model.add(keras.layers.Flatten())
    for i in range(NConvLayers):
        model.add(Dense(40,activation='relu'))
    
    model.add(Dropout(0.2))
    model.add(Dense(10,activation='softmax'))
    
    # compile the model
    model.compile(loss=keras.losses.categorical_crossentropy,
                  optimizer=opt,
                  metrics=['acc'])
    return model

X_test = X_test.astype('float32')

# rescale data in interval [0,1]
X_train /= 255
X_test /= 255



# convert class vectors to binary class matrices, e.g. for use with categorical_crossentropy
Y_train = keras.utils.to_categorical(Y_train, num_classes)
Y_test = keras.utils.to_categorical(Y_test, num_classes)

# Consider an array of 5 labels out of a set of 3 classes {0, 1, 2}:
labels = np.array([0, 2, 1, 2, 0])
# `to_categorical` converts this into a matrix with as many columns as there are classes.
# The number of rows stays the same.
keras.utils.to_categorical(labels)

from tensorflow.keras.optimizers import SGD, Adam, RMSprop, Adagrad, Adadelta, Adam, Adamax, Nadam


#print('Model compiled successfully and ready to be trained.')


# training parameters
batch_size = 32
#epochs

# create the deep neural net
'''
path_to_file='models/model_CNN_NConv_%d_NDeep_%d_Drop_%f_NMax_%d_NAvg_%d_NEp_%d.h5'%(NConvLayers, NDeepLayers, Drop, NMaxPool, NAvgPool, 21)
print(path_to_file)

model_CNN= keras.models.load_model(filepath=path_to_file)


# train CNN and store training info in history
history = model_CNN.fit(X_train, Y_train,
          batch_size=batch_size,
          epochs=epochs,
          verbose=1,
          validation_data=(X_test, Y_test))
'''
path_to_file='models/model_OPT_%s_NEp_%d.h5'%(opt, epochs)
epochs_eff=epochs

for i in reversed(range(epochs)):
    if os.path.exists(path_to_file):
        epochs_eff-=i+1
        model_DNN= keras.models.load_model(filepath=path_to_file)
        print('ESTISTE!!!!', path_to_file, epochs_eff)
        break
    else:
        print('Non esiste fino a ',i+1)
        path_to_file='models/model_OPT_%s_NEp_%d.h5'%(opt, i)


# train DNN and store training info in history
history = model_DNN.fit(X_train, Y_train,
          batch_size=batch_size,
          epochs=epochs_eff,
          verbose=1,
          validation_data=(X_test, Y_test))







save_model_path='models/model_CNN_NConv_%d_NDeep_%d_Drop_%f_NMax_%d_NAvg_%d_NEp_%d.h5'%(NConvLayers, NDeepLayers, Drop, NMaxPool, NAvgPool, 21+epochs)
model_CNN.save(filepath=save_model_path, include_optimizer=True)