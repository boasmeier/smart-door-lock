from flask import Flask
from flask_cors import CORS
import connexion
from waitress import serve
from mqtt_client.client import MqttClient
from mqtt_client.paho_client import PahoClient
import logging
import logging.config
from os import path
from backend_service import BackendService

logging.config.fileConfig(path.join(path.dirname(path.abspath(__file__)), 'logger.conf'))

# Create the application instance
app = connexion.FlaskApp(__name__, specification_dir='./')
service = BackendService(site_ids = ["iotlab"])

# Add Swagger
app.add_api('swagger.yaml')
CORS(app.app)

# If we're running in stand alone mode, run the application
if __name__ == '__main__':
    serve(app, host='0.0.0.0', port=5001)
    #app.run(host='0.0.0.0', port=5000, debug=True) --> for debug mode
