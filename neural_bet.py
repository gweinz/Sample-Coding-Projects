import pandas as df
from keras.models import Sequential
from keras.layers import Dense
from keras.callbacks import EarlyStopping


# team_df = df.read_csv('team_stats_2018-2019.csv')
team_df = df.read_csv('stats.csv')
results_df = df.read_csv('results_2018-2019.csv')

results_df.drop('Date',1,inplace=True)
results_df.drop('Start (ET)',1,inplace=True)

combined = df.merge(results_df, team_df, left_on='Home/Neutral', right_on='Team')
withBoth = df.merge(combined, team_df, left_on='Visitor/Neutral', right_on='Team')

early_stopping_monitor = EarlyStopping(patience=3)

pre_train = withBoth.drop({'Visitor/Neutral', 'Home/Neutral','Team_x', 'Team_y'}, 1)

pre_train['total_points'] = pre_train.apply(lambda x: x['PTS'] + x['PTS.1'], axis=1)

pre_train.drop({'PTS', 'PTS.1'}, 1, inplace=True)

to_train_x = pre_train.drop('total_points', 1)



to_train_y = pre_train['total_points']

# create model
model = Sequential()

#get number of columns in training data
n_cols = to_train_x.shape[1]

# add model layers
model.add(Dense(15, activation='relu', input_shape=(n_cols,)))
model.add(Dense(10, activation='relu'))

model.add(Dense(1))

model.compile(optimizer='adam', loss='mean_squared_error')

model.fit(to_train_x, to_train_y, validation_split=0.2, epochs=1000)

test = df.read_csv('to_test.csv')


test_y_predictions = model.predict(test)

print(test_y_predictions)


