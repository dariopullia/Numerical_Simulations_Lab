import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import backend as K
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Activation
from tensorflow.keras.utils import get_custom_objects
import sys
import numpy as np
import matplotlib.pyplot as plt


datasize=int(sys.argv[1])
epochs=int(sys.argv[2])
# target parameters of f(x) = m*x + b
m = 2 # slope
b = 1 # intersect



# generate training inputs
np.random.seed(0)
x_train = np.random.uniform(-1, 1, int(10*datasize/11))
x_valid = np.random.uniform(-1, 1, int(datasize/11))
x_valid.sort()
y_target = m * x_valid + b # ideal (target) linear function

sigma = 0.8 # noise standard deviation
y_train = np.random.normal(m * x_train + b, sigma) # actual measures from which we want to guess regression parameters
y_valid = np.random.normal(m * x_valid + b, sigma)

model = tf.keras.Sequential()
model.add(Dense(1, input_shape=(1,)))

# compile the model choosing optimizer, loss and metrics objects
model.compile(optimizer='sgd', loss='mse', metrics=['mse'])

# get a summary of our composed model
model.summary()
# fit the model using training dataset
# over 10 epochs of 32 batch size each
# report training progress against validation data
history = model.fit(x=x_train, y=y_train, 
          batch_size=32, epochs=epochs,
          shuffle=True, # a good idea is to shuffle input before at each epoch
          validation_data=(x_valid, y_valid))


# return weights and biases
model.get_weights()


# evaluate model
score = model.evaluate(x_valid, y_valid, batch_size=32, verbose=1)

save_model_path='models/model_data_%s_Ep_%s.h5'%(datasize, epochs)
model.save(filepath=save_model_path, include_optimizer=True)