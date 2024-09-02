import lmdb


db_path = 'src/DataBase/KLINE_1MIN/FUTU/HSImain/'
env = lmdb.open(db_path, readonly=True)

with env.begin() as txn:
    cursor = txn.cursor()
    for key, value in cursor:
        # Assuming the value contains image data (e.g., bytes)
        print(value)

        # Process the image as needed (e.g., display, save, etc.)
        # ...

env.close()