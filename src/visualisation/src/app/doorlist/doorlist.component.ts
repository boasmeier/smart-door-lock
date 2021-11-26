import {Component, OnInit} from '@angular/core';

import {DoorlockService} from "../doorlock_service/doorlock.service";

// Toast Notifications
import {ToastrService} from "ngx-toastr";
import {animate, state, style, transition, trigger} from "@angular/animations";

export interface Door {
  deviceId: number,
  name: string,
  doorState: string,
  lockState: string,
  events: Event[]
}

export interface Event {
  datetime: Date
  event: string
  message: string
}

@Component({
  selector: 'app-doorlist',
  templateUrl: './doorlist.component.html',
  styleUrls: ['./doorlist.component.css'],
  animations: [
    trigger('detailExpand', [
      state('collapsed', style({height: '0px', minHeight: '0'})),
      state('expanded', style({height: '*'})),
      transition('expanded <=> collapsed', animate('225ms cubic-bezier(0.4, 0.0, 0.2, 1)'))
    ]),
  ],
})
export class DoorlistComponent implements OnInit {

  doors: Door[] = []


  interval = 5000;
  doorlistColumns: string[] = ['deviceId', 'name', 'doorState', 'lockState', 'button'];
  eventlistColumns: string[] = ['datetime', 'event', 'message'];
  expandedElement: Event | null;

  constructor(private doorListService: DoorlockService,
              private toastr: ToastrService) {
    this.expandedElement = null
    this.interval = setInterval(() => {
      this.refresh();
    }, this.interval);

    this.refresh();
  }

  ngOnInit(): void {
    // empty
  }

  ngOnDestroy() {
    if (this.interval) {
      clearInterval(this.interval);
    }
  }

  refresh() {
    this.doorListService.getData<Door[]>("iotlab").subscribe({
      next: data => {
        this.doors = data
      },
      error: error => {
        this.toastr.error("Unable to reach server");
        console.error(error);
      }
    });

    for (let door of this.doors) {
      this.doorListService.getDeviceData<Event[]>('iotlab', door.deviceId, 'event').subscribe({
        next: data => {
          door.events = data
        },
        error: error => {
          this.toastr.error("Unable to reach server");
          console.error(error);
        }
      })
    }
  }

  onOpenBtnClick(deviceId: number) {
    console.log("Sending request to open lock with id: ", deviceId);
    this.doorListService.sendAction("iotlab", deviceId, {action: 'unlock'}).subscribe({
      next: (msg) => {
        console.log(msg);
      },
      error: (error) => {
        this.toastr.error("There occured an error while sending the request");
        console.error(error);
      }
    });
  }
}
