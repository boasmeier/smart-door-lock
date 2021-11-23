import {NgModule} from '@angular/core';
import {RouterModule, Routes} from "@angular/router";
import {DoorlistComponent} from "./doorlist/doorlist.component";
import {LoggerComponent} from "./logger/logger.component";


const routes: Routes = [
  {path: '', component: DoorlistComponent},
  {path: 'logs', component: LoggerComponent}
];


@NgModule({
  declarations: [],
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule {
}

export const routerComponents = [DoorlistComponent, LoggerComponent]
