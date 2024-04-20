import requests

def test_api(image_path):
    # url = 'http://127.0.0.1:5000/upload'  # Update the URL if your Flask server is running on a different host or port
    # url = 'https://69766b76-41ca-4aa9-80b3-a8823de7fc38-00-se4nro7x7qoo.picard.replit.dev/upload'  # Update the URL if your Flask server is running on a different host or port
    url = 'https://f9698e73-3671-48d9-a096-9832ceeffc5f-00-3e2zpfrvccauz.pike.replit.dev/upload'  # Update the URL if your Flask server is running on a different host or port

    # Read the image file
    with open(image_path, 'rb') as f:
        files = {'image': f}

        # Send POST request to the Flask API
        response = requests.post(url, files=files)

        # Print response
        print('Response:', response.content)
        # print(response.json())


if __name__ == '__main__':
    # Provide the path to the image you want to upload
    # image_path = 'app-ring.png'
    image_path = 'theft-icon.png'
    test_api(image_path)
