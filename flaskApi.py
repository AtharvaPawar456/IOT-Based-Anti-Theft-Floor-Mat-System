from flask import Flask, request, jsonify, render_template
import time
import os
from datetime import datetime
import shutil


app = Flask(__name__)


@app.route('/')
def home():
    return render_template('index.html')
  
@app.route('/history')
def history():
    # Read all filenames and extract timestamps
    files_with_timestamp = []
    try:
        filenames = os.listdir('static')
        print("filenames ", filenames )
        for filename in filenames:
          if filename.startswith('uploaded_image') and filename != 'uploaded_image.jpg':
              parts = filename.split('#')
              filedate  = str(parts[-2].split('.')[0])  # Extract timestamp from filename
              filetime  = str(parts[-1].split('.')[0])  # Extract timestamp from filename
              files_with_timestamp.append({'filename': filename, 'filedate': filedate, 'filetime': filetime})
    except Exception as e:  
        print('Error:', str(e))
    return render_template('history.html', content=files_with_timestamp)
  

@app.route('/upload', methods=['POST'])
def upload():
    # Print the payload
    # payload = request.get_json()
    # print('Payload:', payload)
  
    if 'image' not in request.files:
        error_message = 'No image found in the request'
        print('Error:', error_message)
        return jsonify({'error': error_message}), 400
    image = request.files['image']
    if image.filename == '':
        error_message = 'No selected file'
        print('Error:', error_message)
        return jsonify({'error': error_message}), 400
    try:
        # timestamp = int(time.time())
        current_datetime = datetime.now()
        timestamp = current_datetime.strftime("%Y_%m_%d#%H_%M_%S")


        filename = f'static/uploaded_image#{timestamp}.jpg'
        image.save(filename)
        time.sleep(.2)
        # image.save('static/uploaded_image.jpg')

        destination = 'static/uploaded_image.jpg'
        shutil.copyfile(filename, destination)
  
             
        # image.save(filename)
        print('Image saved successfully')
        return jsonify({'message': 'Image uploaded successfully'}), 200
    except Exception as e:
        error_message = 'Failed to save image: ' + str(e)
        print('Error:', error_message)
        return jsonify({'error': error_message}), 500


if __name__ == '__main__':
  # app.run(debug=True)
  # app.run(host='0.0.0.0', port=80)
  app.run(debug=True, host='0.0.0.0', port=80)


# Old Code
'''
# @app.route('/upload', methods=['POST'])
# def upload():
#     if 'image' not in request.files:
#         return jsonify({'error': 'No image found'}), 400
#     image = request.files['image']
#     # Do something with the image, like save it to disk or process it
#     image.save('uploaded_image.jpg')
#     return jsonify({'message': 'Image uploaded successfully'}), 200

# @app.route('/')
# def home():
#     return 'Hello'

'''