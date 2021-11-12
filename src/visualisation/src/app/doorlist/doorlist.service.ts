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
        id: 1,
        name: 'Main door',
        status: 'closed'
      },
      {
        id: 2,
        name: 'Back door',
        status: 'closed'
      }
    ]

  }
}
