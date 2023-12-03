from everywhereml.data import Dataset
from everywhereml.data.collect import SerialCollector

"""
Create a SerialCollector object.
Each data line is marked by the 'IMU:' string
Collect 30 seconds of data for each gesture
Replace the port with your own!

If a imu.csv file already exists, skip collection
"""

try:
    imu_dataset = Dataset.from_csv(
        'imu.csv', 
        name='ContinuousMotion', 
        target_name_column='target_name'
    )
    print(imu_dataset.describe())
    
except FileNotFoundError:
    imu_collector = SerialCollector(
        # port='/dev/cu.usbmodem141401', 
        port='COM3', 
        baud=115200, 
        start_of_frame='IMU:', 
        feature_names=['ax', 'ay', 'az', 'gx', 'gy', 'gz']
    )
    imu_dataset = imu_collector.collect_many_classes(
        dataset_name='ContinuousMotion', 
        duration=10
    )
    
    # save dataset to file for later use
    imu_dataset.df.to_csv('imu.csv', index=False)

imu_dataset.plot.features_pairplot(n=300)