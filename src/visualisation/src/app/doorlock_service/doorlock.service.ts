import {Injectable} from '@angular/core';

// REST
import {HttpClient} from "@angular/common/http";
import {Observable} from "rxjs";

@Injectable({
  providedIn: 'root'
})
export class DoorlockService {

  baseUrl = "http://localhost:5004/doorlocks"

  constructor(private http: HttpClient) {
  }

  getData<T>(siteId: string): Observable<T> {
    let url = this.baseUrl + `/${siteId}`;
    return this.http.get<T>(url);
  }

  sendAction(siteId: string, deviceId: number, body: any) {
    let url = this.baseUrl + `/${siteId}/${deviceId}/action`;
    return this.http.post<any>(url, body);
  }
}
