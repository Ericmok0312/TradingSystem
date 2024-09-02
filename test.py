import lmdb


db_path = 'src/DataBase/KLINE_1MIN/FUTU/HSImain/'
env = lmdb.open(db_path, readonly=True)

count = 0
with env.begin() as txn:
    cursor = txn.cursor()
    for key, value in cursor:
        # Assuming the value contains image data (e.g., bytes)
        count+=1

        # Process the image as needed (e.g., display, save, etc.)
        # ...

env.close()
print(count)