import {Component, OnInit} from '@angular/core';

import {DoorlistService} from "./doorlist.service";

interface Door {
  deviceId: number,
  name: string,
  doorState: string,
  lockState: string
}

@Component({
  selector: 'app-doorlist',
  templateUrl: './doorlist.component.html',
  styleUrls: ['./doorlist.component.css']
})
export class DoorlistComponent implements OnInit {

  doors: Door[] = []

  constructor(private doorlist: DoorlistService) {
    this.doorlist.getData<Door[]>("iotlab").subscribe(data =>
      this.doors = data
    );
  }

  ngOnInit(): void {
    // empty
  }

  onOpenBtnClick(deviceId: number) {
    console.log("Opening lock with id: ", deviceId);
    this.doorlist.sendAction("iotlab", deviceId);
    window.location.reload();
  }
}
