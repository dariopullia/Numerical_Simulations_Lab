import tensorflow as tf
from tensorflow import keras
import os

import sys
import numpy as np
import matplotlib.pyplot as plt
seed=0
np.random.seed(seed) # fix random seed
tf.random.set_random_seed(seed)

from tensorflow.keras.datasets import mnist


epochs=int(sys.argv[1])
opt=sys.argv[2]
print(epochs,opt)



# input image dimensions
img_rows, img_cols = 28, 28 # number of pixels 
# output
num_classes = 10 # 10 digits

# the data, split between train and test sets
(X_train, Y_train), (X_test, Y_test) = mnist.load_data()

# reshape data, it could depend on tensorflow.keras backend
X_train = X_train.reshape(X_train.shape[0], img_rows*img_cols)
X_test = X_test.reshape(X_test.shape[0], img_rows*img_cols)

# cast floats to single precision
X_train = X_train.astype('float32')

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout

def create_DNN():
    # instantiate model
    model = Sequential()
    # add a dense all-to-all relu layer
    model.add(Dense(400,input_shape=(img_rows*img_cols,), activation='relu'))
    # add a dense all-to-all relu layer
    model.add(Dense(100, activation='relu'))
    # apply dropout with rate 0.5
    model.add(Dropout(0.5))
    # soft-max layer
    model.add(Dense(num_classes, activation='softmax'))
    
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

def compile_model():
    # create the model
    model=create_DNN()
    # compile the model
    model.compile(loss=keras.losses.categorical_crossentropy,
                  optimizer=opt,
                  metrics=['acc'])
    return model

#print('Model compiled successfully and ready to be trained.')


# training parameters
batch_size = 32
#epochs

# create the deep neural net
model_DNN = compile_model()


#ma posso continuare l'allenamento!!!!!
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




save_model_path='models/model_OPT_%s_NEp_%d.h5'%(opt, epochs)
model_DNN.save(filepath=save_model_path, include_optimizer=True)