import { Component, OnInit } from '@angular/core';
import { INoticia } from 'src/app/data/data';
import { NewsService } from 'src/app/news.service';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css']
})
export class HomeComponent implements OnInit {

  noticias: INoticia[] | any

  constructor(private newsService: NewsService) { }

  ngOnInit(): void {

    this.noticias = this.newsService.getAll()
  }

}
