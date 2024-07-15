import lmdb

# Open the LMDB environment
env = lmdb.open("/data/home/emk/Coding/Trading_system/TradingSystem/src/DataBase/Futu/02222/", readonly=True)

# Start a new transaction
with env.begin() as txn:
    # Create a cursor to iterate through the database
    cursor = txn.cursor()
    for key, value in cursor:
        print(f'Key: {key}, Value: {value}')