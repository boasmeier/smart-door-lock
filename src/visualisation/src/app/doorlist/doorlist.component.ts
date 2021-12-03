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
  datetime: string
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
  expandedElement: Door | undefined;

  constructor(private doorListService: DoorlockService,
              private toastr: ToastrService) {
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
      next: doors => {
        for (let door of doors) {
          this.doorListService.getDeviceData<Event[]>('iotlab', door.deviceId, 'event').subscribe({
            next: events => {
              door.events = events
            },
            error: error => {
              this.toastr.error("Unable to reach server");
              console.error(error);
            }
          })
        }

        this.doors = doors
      },
      error: error => {
        this.toastr.error("Unable to reach server");
        console.error(error);
      }
    });
  }

  handleBtnClick(deviceId: number) {
    // Check if the door is locked or not
    let locked = this.doors.some(function (door) {
      if (door['deviceId'] == deviceId) {
        return door['lockState'] == "locked";
      }
      return null;
    });

    if (locked) { // Unlock if it is locked
      console.log("Sending request to unlock the lock with id: ", deviceId);
      this.doorListService.sendAction("iotlab", deviceId, {action: 'unlock'}).subscribe({
        next: (msg) => {
          console.log(msg);
        },
        error: (error) => {
          this.toastr.error("There occured an error while sending the request");
          console.error(error);
        }
      });
    } else { // Lock if it is unlocked
      console.log("Sending request to lock the lock with id: ", deviceId);
      this.doorListService.sendAction("iotlab", deviceId, {action: 'lock'}).subscribe({
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
}
