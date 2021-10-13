from flask import Flask
from flask_cors import CORS
import connexion
from waitress import serve

# Create the application instance
app = connexion.FlaskApp(__name__, specification_dir='./')

# Add Swagger
app.add_api('swagger.yaml')
CORS(app.app)

# If we're running in stand alone mode, run the application
if __name__ == '__main__':
    serve(app, host='0.0.0.0', port=5001)
    #app.run(host='0.0.0.0', port=5000, debug=True) --> for debug mode
