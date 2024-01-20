import { Injectable } from '@angular/core';
import { INoticia, noticias } from './data/data';


@Injectable({
  providedIn: 'root'
})
export class NewsService {
  noticias: INoticia[] = noticias

  constructor() { }

    getAll(){
      return this.noticias
    }

    getOne(newsId: number){
      return this.noticias.find(noticia => noticia.id === newsId)
    }

}
