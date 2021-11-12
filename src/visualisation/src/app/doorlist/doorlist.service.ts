import {Injectable} from '@angular/core';

// REST
import {HttpClient} from "@angular/common/http";
import {Observable} from "rxjs";

@Injectable({
  providedIn: 'root'
})
export class DoorlistService {

  constructor(private http: HttpClient) {
  }

  getData<T>(siteId: string): Observable<T> {
    let url = `http://localhost:5001/doorlocks/${siteId}`;
    return this.http.get<T>(url);
  }

  sendAction(siteId: string, deviceId: number) {
    let url = `http://localhost:5001/doorlocks/${siteId}/${deviceId}/action`;
    this.http.post<any>(url, {action: 'unlock'}).subscribe(); // .pipe()?
  }
}
