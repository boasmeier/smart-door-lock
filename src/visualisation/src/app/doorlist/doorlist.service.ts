import {Injectable} from '@angular/core';

// REST
import {HttpClient} from "@angular/common/http";

@Injectable({
  providedIn: 'root'
})
export class DoorlistService {

  constructor(private http: HttpClient) {
  }

  getData() {
    let url = "localhost:5001/doorlocks/iotlab/";
    // return this.http.get(url);

    return [
      {
        deviceId: "1",
        doorState: "open",
        lockState: "unlocked",
        name: "Main Entrance [1]"
      },
      {
        deviceId: "2",
        doorState: "open",
        lockState: "unlocked",
        name: "Back Entrance [2]"
      }
    ]

  }
}
