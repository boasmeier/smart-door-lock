import {NgModule} from '@angular/core';
import {RouterModule, Routes} from '@angular/router';

// Routed pages
import {DoorlistComponent} from "./doorlist/doorlist.component";
import {LoggerComponent} from "./logger/logger.component";

const routes: Routes = [
  {path: '', component: DoorlistComponent},
  {path: 'logs', component: LoggerComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule {
}

export const routingComponents = [DoorlistComponent, LoggerComponent]
