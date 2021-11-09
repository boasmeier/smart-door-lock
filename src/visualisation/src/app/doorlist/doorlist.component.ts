import {Component, OnInit} from '@angular/core';

import {DoorlistService} from "./doorlist.service";

@Component({
  selector: 'app-doorlist',
  templateUrl: './doorlist.component.html',
  styleUrls: ['./doorlist.component.css']
})
export class DoorlistComponent implements OnInit {

  data: any[] = []

  constructor(private doorlist: DoorlistService) {
    // this.doorlist.getData().subscribe(data => {
    //     this.data = data; // maybe data.json()
    //   }
    // )
    this.data = this.doorlist.getData();
  }

  ngOnInit(): void {
    // empty
  }

}
