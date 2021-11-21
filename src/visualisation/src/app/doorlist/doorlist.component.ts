import {Component, OnInit} from '@angular/core';

import {DoorlistService} from "./doorlist.service";

// Toast Notifications
import {ToastrService} from "ngx-toastr";

export interface Door {
  deviceId: number,
  name: string,
  doorState: string,
  lockState: string
}

@Component({
  selector: 'app-doorlist',
  templateUrl: './doorlist.component.html',
  styleUrls: ['./doorlist.component.css'],
})
export class DoorlistComponent implements OnInit {

  doors: Door[] = []
  interval = 5000;
  displayedColumns: string[] = ['deviceId', 'name', 'doorState', 'lockState', 'button'];

  constructor(private doorListService: DoorlistService,
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
      next: data => {
        this.doors = data
      },
      error: error => {
        this.toastr.error("Unable to reach server");
        console.error(error);
      }
    });
  }

  onOpenBtnClick(deviceId: number) {
    console.log("Sending request to open lock with id: ", deviceId);
    this.doorListService.sendAction("iotlab", deviceId).subscribe({
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
