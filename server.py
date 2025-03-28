from flask import Flask, request, jsonify
import json
from datetime import datetime

app = Flask(__name__)

# store retrieved data
data_log = []

@app.route("/", methods=["POST"])
def save_weather_data():
    try:
        # get json data
        data = request.get_json()

        if not data:
            return jsonify({"status": "error", "message": "Invalid JSON"}), 400

        # record the time
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        data_with_time = {
            "data": data,
            "received_at": timestamp
        }

        # save it to our log
        data_log.append(data_with_time)

        # into our json file
        with open("weather_data.json", "a") as file:
            json.dump(data_with_time, file)
            file.write("\n")

        return jsonify({"status": "success", "message": "Data saved", "received_at": timestamp}), 200
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500


@app.route("/logs", methods=["GET"])
def get_logs():
    # return all the saved json
    return jsonify(data_log), 200


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)